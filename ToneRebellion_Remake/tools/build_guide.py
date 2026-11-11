"""Builds web/guide.html from docs/game-guide.md (needs the `markdown` package).

Usage: python tools/build_guide.py
The page is published next to the browser build (site/guide.html).
"""
import pathlib
import re

import markdown

ROOT = pathlib.Path(__file__).resolve().parent.parent
SOURCE = ROOT / "docs" / "game-guide.md"
TARGET = ROOT / "web" / "guide.html"
REPO = "https://github.com/Fadoli/Tone-Rebellion-Remastered/tree/main/"

TEMPLATE = """<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Tone Rebellion Guide</title>
<meta name="description" content="Tone Rebellion (1997): what unlocks when, glyph bonuses, difficulty effects, unit, spell and building stats.">
<style>
  :root {{ color-scheme: dark; --bg: #0b0d12; --panel: #161a23; --text: #e6e8ee;
          --muted: #9aa1b1; --accent: #7fb2ff; --border: #2a3040; --row: #121620; }}
  html, body {{ margin: 0; background: var(--bg); color: var(--text);
               font: 15px/1.6 system-ui, sans-serif; }}
  main {{ max-width: 60rem; margin: 0 auto; padding: 2.5rem 1rem 4rem; }}
  a {{ color: var(--accent); }}
  h1 {{ margin: 0 0 .5rem; font-size: 2rem; line-height: 1.2; }}
  h2 {{ margin: 2.75rem 0 .75rem; padding-top: .5rem; font-size: 1.4rem;
        border-top: 1px solid var(--border); }}
  h3 {{ margin: 1.75rem 0 .5rem; font-size: 1.1rem; }}
  p, li {{ color: var(--muted); }}
  strong {{ color: var(--text); }}
  code {{ font: .9em ui-monospace, Consolas, monospace; }}
  .back {{ display: inline-block; margin-bottom: 1.5rem; }}
  .t {{ overflow-x: auto; margin: .75rem 0; border: 1px solid var(--border);
        border-radius: 8px; }}
  table {{ border-collapse: collapse; width: 100%; font-size: .92rem; }}
  th, td {{ padding: .4rem .7rem; text-align: left; vertical-align: top;
            border-bottom: 1px solid var(--border); }}
  th {{ background: var(--panel); color: var(--text); white-space: nowrap; }}
  td {{ color: var(--text); }}
  tbody tr:nth-child(even) td {{ background: var(--row); }}
  tbody tr:last-child td {{ border-bottom: 0; }}
  ol li, ul li {{ margin: .2rem 0; }}
</style>
</head>
<body>
<main>
<a class="back" href="./">&larr; Play in the browser</a>
{body}
</main>
</body>
</html>
"""


def main():
    text = SOURCE.read_text(encoding="utf-8")
    # Links into the repository point at GitHub on the published page.
    text = re.sub(r"\]\(\.\./\.\./([^)]*)\)", lambda m: "](" + REPO + m.group(1) + ")", text)
    body = markdown.markdown(text, extensions=["tables", "toc"])
    body = body.replace("<table>", '<div class="t"><table>').replace("</table>", "</table></div>")
    with open(TARGET, "w", encoding="utf-8", newline="\n") as out:
        out.write(TEMPLATE.format(body=body))


if __name__ == "__main__":
    main()
