"""Builds the website's text pages from the repository's Markdown files.

    web/guide.html      <- docs/game-guide.md
    web/changelog.html  <- CHANGELOG.md   ("What's new")

Usage: python tools/build_pages.py [--site DIR]   (needs the `markdown` package)
With --site, also assembles the published site in DIR: the browser build
from web/out (tools/build_web.sh) as index.html plus these pages. The release
workflow does the same.
"""
import argparse
import pathlib
import posixpath
import re
import shutil

import markdown

ROOT = pathlib.Path(__file__).resolve().parent.parent
REPO_ROOT = ROOT.parent
GITHUB = "https://github.com/Fadoli/Tone-Rebellion-Remastered"

# Repository file (relative to the repository root) -> page on the site.
PAGES = [
    {"source": "ToneRebellion_Remake/docs/game-guide.md", "target": "guide.html",
     "nav": "guide", "title": "Tone Rebellion Guide", "toc_depth": "2-3",
     "description": "Tone Rebellion (1997) game guide: what unlocks when in each world, "
                    "glyph bonuses, difficulty effects, unit, spell and building stats.",
     "chips": [("what-unlocks-when", "Unlocks per world"), ("glyphs", "Glyphs"),
               ("difficulty", "Difficulty"), ("tribe-units", "Units"),
               ("spells", "Spells"), ("leviathan-defences", "Leviathan defences")]},
    {"source": "ToneRebellion_Remake/CHANGELOG.md", "target": "changelog.html",
     "nav": "changelog", "title": "Tone Rebellion Remastered: What's new", "toc_depth": "2",
     "description": "What changed in each version of Tone Rebellion Remastered.",
     "chips": []},
]
SITE_LINKS = {page["source"]: page["target"] for page in PAGES}

STYLE = """
  :root { color-scheme: dark; --bg: #0b0d12; --panel: #161a23; --panel2: #10141c;
          --text: #e6e8ee; --muted: #9aa1b1; --accent: #7fb2ff; --border: #2a3040;
          --head: 3.5rem; }
  * { box-sizing: border-box; }
  html { scroll-padding-top: calc(var(--head) + 1rem); scroll-behavior: smooth; }
  html, body { margin: 0; background: var(--bg); color: var(--text);
               font: 15px/1.6 system-ui, sans-serif; }
  a { color: var(--accent); }
  code { font: .88em ui-monospace, Consolas, monospace; padding: .05em .3em;
         background: var(--panel); border-radius: 4px; }

  .site { position: sticky; top: 0; z-index: 10; height: var(--head);
          background: rgba(11, 13, 18, .92); backdrop-filter: blur(6px);
          border-bottom: 1px solid var(--border); }
  .site .bar { max-width: 76rem; height: 100%; margin: 0 auto; padding: 0 1rem;
               display: flex; align-items: center; gap: 1.5rem; }
  .brand { color: var(--text); font-weight: 700; text-decoration: none;
           white-space: nowrap; letter-spacing: .01em; }
  .brand span { color: var(--accent); }
  .site nav { display: flex; gap: .25rem; overflow-x: auto; scrollbar-width: none; }
  .site nav a { padding: .35rem .7rem; border-radius: 6px; color: var(--muted);
                text-decoration: none; white-space: nowrap; }
  .site nav a:hover, .site nav a[aria-current] { color: var(--text); background: var(--panel); }
  .site nav a.play { color: #0b0d12; background: var(--accent); font-weight: 600; }

  .layout { max-width: 76rem; margin: 0 auto; padding: 0 1rem;
            display: grid; grid-template-columns: 15rem minmax(0, 1fr); gap: 2.5rem; }
  .toc { position: sticky; top: calc(var(--head) + 1.5rem); align-self: start;
         max-height: calc(100vh - var(--head) - 3rem); overflow-y: auto;
         padding: .25rem 0 1rem; font-size: .9rem; }
  .toc summary { display: none; }
  .toc .label { margin: 0 0 .5rem; color: var(--muted); font-size: .75rem;
                text-transform: uppercase; letter-spacing: .08em; }
  .toc ul { list-style: none; margin: 0; padding: 0; }
  .toc ul ul { margin: .1rem 0 .3rem .75rem; font-size: .85rem; }
  .toc a { display: block; padding: .2rem .6rem; border-left: 2px solid transparent;
           color: var(--muted); text-decoration: none; }
  .toc a:hover { color: var(--text); }
  .toc a.active { color: var(--text); border-left-color: var(--accent); }
  main { padding: 2.5rem 0 4rem; min-width: 0; }

  .hero h1 { margin: 0; font-size: 2.2rem; line-height: 1.2; }
  .hero p { max-width: 46rem; }
  .chips { display: flex; flex-wrap: wrap; gap: .5rem; margin: 1rem 0 0; padding: 0; }
  .chips a { padding: .3rem .75rem; border: 1px solid var(--border); border-radius: 999px;
             color: var(--text); text-decoration: none; font-size: .9rem; }
  .chips a:hover { border-color: var(--accent); }
  main h2 { margin: 3rem 0 .75rem; padding-top: 1.25rem; font-size: 1.5rem;
            border-top: 1px solid var(--border); }
  main h3 { margin: 2rem 0 .5rem; font-size: 1.12rem; }
  .headerlink { margin-left: .4rem; color: var(--border); text-decoration: none;
                font-weight: 400; visibility: hidden; }
  h2:hover .headerlink, h3:hover .headerlink { visibility: visible; }
  .headerlink:hover { color: var(--accent); }
  main p, main li { color: var(--muted); max-width: 52rem; }
  main strong { color: var(--text); }
  main ul { padding-left: 1.25rem; }
  main li { margin: .3rem 0; }
  .t { overflow-x: auto; margin: .9rem 0 1.25rem; border: 1px solid var(--border);
       border-radius: 10px; background: var(--panel2); }
  table { border-collapse: collapse; width: 100%; font-size: .9rem; }
  th, td { padding: .45rem .75rem; text-align: left; vertical-align: top;
           border-bottom: 1px solid var(--border); }
  th { position: sticky; top: 0; background: var(--panel); color: var(--text);
       font-weight: 600; white-space: nowrap; }
  td { color: var(--text); }
  td:first-child { font-weight: 500; }
  tbody tr:hover td { background: #1a2030; }
  tbody tr:last-child td { border-bottom: 0; }

  footer { margin-top: 4rem; padding: 1.5rem 0 0; border-top: 1px solid var(--border);
           color: var(--muted); font-size: .85rem; }
  .top { position: fixed; right: 1rem; bottom: 1rem; width: 2.5rem; height: 2.5rem;
         display: grid; place-items: center; border: 1px solid var(--border);
         border-radius: 50%; background: var(--panel); color: var(--text);
         text-decoration: none; opacity: 0; pointer-events: none; transition: opacity .2s; }
  .top.show { opacity: 1; pointer-events: auto; }

  @media (max-width: 900px) {
    .layout { display: block; }
    .toc { position: static; max-height: none; margin: 1rem 0 0; padding: 0;
           border: 1px solid var(--border); border-radius: 10px; background: var(--panel2); }
    .toc summary { display: block; padding: .6rem .9rem; cursor: pointer; font-weight: 600; }
    .toc .label { display: none; }
    .toc > ul { padding: 0 .5rem .75rem; }
    main { padding-top: 1.5rem; }
    .hero h1 { font-size: 1.8rem; }
  }
  @media (max-width: 560px) {
    .site .bar { gap: .75rem; }
    .brand .long { display: none; }
  }
"""

SCRIPT = """
(function () {
  // Contents open beside the text on wide screens, folded on phones.
  var toc = document.getElementById('toc');
  var wide = window.matchMedia('(min-width: 901px)');
  function sync() { toc.open = wide.matches; }
  sync(); wide.addEventListener('change', sync);
  toc.addEventListener('click', function (e) {
    if (e.target.tagName === 'A' && !wide.matches) toc.open = false;
  });
  // Highlight the section in view and show the back-to-top button.
  var links = {};
  toc.querySelectorAll('a').forEach(function (a) { links[a.hash.slice(1)] = a; });
  var heads = document.querySelectorAll('main h2[id], main h3[id]');
  var upButton = document.querySelector('.top');
  function onScroll() {
    var current = null;
    heads.forEach(function (h) { if (h.getBoundingClientRect().top < 120) current = h.id; });
    toc.querySelectorAll('a.active').forEach(function (a) { a.classList.remove('active'); });
    if (current && links[current]) links[current].classList.add('active');
    upButton.classList.toggle('show', window.scrollY > 600);
  }
  window.addEventListener('scroll', onScroll, { passive: true }); onScroll();
})();
"""

NAV = [("guide", "guide.html", "Guide"), ("changelog", "changelog.html", "What's new"),
       (None, GITHUB + "/releases", "Download"), (None, GITHUB, "Source")]


def page_html(page, hero, toc, body):
    nav = ['<a class="play" href="./">Play</a>']
    for key, href, label in NAV:
        current = ' aria-current="page"' if key == page["nav"] else ""
        nav.append('<a href="%s"%s>%s</a>' % (href, current, label))
    chips = "".join('<a href="#%s">%s</a>' % chip for chip in page["chips"])
    chips = '<p class="chips">%s</p>' % chips if chips else ""
    source_url = GITHUB + "/blob/main/" + page["source"]
    return """<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>%(title)s</title>
<meta name="description" content="%(description)s">
<style>%(style)s</style>
</head>
<body>
<header class="site">
  <div class="bar">
    <a class="brand" href="./">Tone Rebellion <span class="long">Remastered</span></a>
    <nav aria-label="Site">%(nav)s</nav>
  </div>
</header>
<div class="layout">
  <details class="toc" id="toc">
    <summary>Contents</summary>
    <p class="label">On this page</p>
    %(toc)s
  </details>
  <main>
    <div class="hero">%(hero)s%(chips)s</div>
    %(body)s
    <footer>
      Tone Rebellion Remastered is a fan-made remake of <strong>Tone Rebellion</strong>
      (The Logic Factory, 1997); you need your own copy of the game to play.
      <a href="%(source_url)s">This page on GitHub</a>.
    </footer>
  </main>
</div>
<a class="top" href="#" aria-label="Back to top">&uarr;</a>
<script>%(script)s</script>
</body>
</html>
""" % {"title": page["title"], "description": page["description"], "style": STYLE,
       "nav": "".join(nav), "toc": toc, "hero": hero, "chips": chips, "body": body,
       "source_url": source_url, "script": SCRIPT}


def site_link(source, href):
    """Rewrites a relative Markdown link: site pages stay local, other
    repository files point at GitHub."""
    if re.match(r"^[a-z]+:|^#", href):
        return href
    path, _, anchor = href.partition("#")
    target = posixpath.normpath(posixpath.join(posixpath.dirname(source), path))
    anchor = "#" + anchor if anchor else ""
    if target in SITE_LINKS:
        return SITE_LINKS[target] + anchor
    return GITHUB + "/blob/main/" + target + anchor


def toc_list(tokens):
    items = []
    for token in tokens:
        children = toc_list(token["children"]) if token["children"] else ""
        items.append('<li><a href="#%s">%s</a>%s</li>' % (token["id"], token["name"], children))
    return "<ul>" + "".join(items) + "</ul>"


def build(page):
    source = page["source"]
    text = (REPO_ROOT / source).read_text(encoding="utf-8")
    text = re.sub(r"\]\(([^)\s]+)\)", lambda m: "](" + site_link(source, m.group(1)) + ")", text)
    md = markdown.Markdown(extensions=["tables", "toc"], extension_configs={
        "toc": {"toc_depth": page["toc_depth"], "permalink": "#",
                "permalink_title": "Link to this section"}})
    body = md.convert(text)
    # The sidebar replaces a Markdown "Contents" list; the title and intro
    # before the first section become the page header.
    body = re.sub(r'<h2 id="contents">.*?</ol>\s*', "", body, flags=re.S)
    tokens = []
    for token in md.toc_tokens:
        tokens.extend(token["children"] if token["level"] == 1 else [token])
    toc = toc_list([t for t in tokens if t["id"] != "contents"])
    hero_end = body.find("<h2")
    hero, body = body[:hero_end], body[hero_end:]
    hero = re.sub(r'<a class="headerlink"[^>]*>#</a>', "", hero)
    body = body.replace("<table>", '<div class="t"><table>').replace("</table>", "</table></div>")
    with open(ROOT / "web" / page["target"], "w", encoding="utf-8", newline="\n") as out:
        out.write(page_html(page, hero.strip(), toc, body))


def assemble_site(site):
    """Copies the browser build (web/out) and the pages into one folder, as
    published on GitHub Pages: the game page becomes index.html."""
    out = ROOT / "web" / "out"
    site.mkdir(parents=True, exist_ok=True)
    for name, target in (("ToneRebellion_Remake.html", "index.html"),
                         ("ToneRebellion_Remake.js", None),
                         ("ToneRebellion_Remake.wasm", None)):
        shutil.copyfile(out / name, site / (target or name))
    for page in PAGES:
        shutil.copyfile(ROOT / "web" / page["target"], site / page["target"])
    (site / ".nojekyll").touch()


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--site", type=pathlib.Path,
                        help="also assemble the whole site (browser build + pages) here")
    args = parser.parse_args()
    for page in PAGES:
        build(page)
    if args.site:
        assemble_site(args.site)


if __name__ == "__main__":
    main()
