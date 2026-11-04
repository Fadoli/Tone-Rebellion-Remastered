"""Development tool, not needed to build: regenerate src/core/game_session_schema.c: a field table for every struct
reachable from GameSession, written into remake saves so a later build can
copy fields by name. Usage: python tools/gen_session_schema.py . > src/core/game_session_schema.c"""
import os, re, sys

root = sys.argv[1]
headers = []
for d in ('src/core', 'src/data'):
    for n in sorted(os.listdir(os.path.join(root, d))):
        if n.endswith('.h'):
            headers.append(os.path.join(root, d, n))

def strip(text):
    text = re.sub(r'/\*.*?\*/', ' ', text, flags=re.S)
    text = re.sub(r'//[^\n]*', ' ', text)
    return text

structs = {}  # name -> list of (type, name, dims, inner)
tagged = set()

def parse_body(body, owner):
    fields = []
    i = 0
    while i < len(body):
        m = re.match(r'\s*struct\s+(\w+)\s*\{', body[i:])
        if m:
            depth = 1
            j = i + m.end()
            while depth:
                if body[j] == '{': depth += 1
                elif body[j] == '}': depth -= 1
                j += 1
            inner = body[i + m.end():j - 1]
            k = body.index(';', j)
            decl = body[j:k].strip()
            for part in decl.split(','):
                pm = re.match(r'\s*(\w+)\s*((?:\s*\[[^\]]+\])*)\s*$', part)
                name, dims = pm.group(1), re.findall(r'\[([^\]]+)\]', pm.group(2))
                tname = m.group(1)
                tagged.add(tname)
                structs[tname] = parse_body(inner, tname)
                fields.append((tname, name, dims, True))
            i = k + 1
            continue
        k = body.find(';', i)
        if k < 0: break
        decl = body[i:k].strip()
        i = k + 1
        if not decl: continue
        m = re.match(r'((?:unsigned\s+|signed\s+)?\w+)\s+(.*)$', decl, re.S)
        typ, rest = m.group(1), m.group(2)
        assert '*' not in rest and '(' not in rest and ':' not in rest, decl
        for part in rest.split(','):
            pm = re.match(r'\s*(\w+)\s*((?:\s*\[[^\]]+\])*)\s*$', part)
            assert pm, (owner, decl)
            fields.append((typ, pm.group(1), re.findall(r'\[([^\]]+)\]', pm.group(2)), False))
    return fields

for h in headers:
    text = strip(open(h, encoding='utf-8').read())
    for m in re.finditer(r'typedef\s+struct\s+(\w+)\s*\{', text):
        start = m.end()
        depth = 1
        j = start
        while depth:
            if text[j] == '{': depth += 1
            elif text[j] == '}': depth -= 1
            j += 1
        tail = re.match(r'\s*(\w+)\s*;', text[j:])
        if not tail: continue
        try:
            structs[tail.group(1)] = parse_body(text[start:j - 1], tail.group(1))
        except Exception as error:
            structs[tail.group(1)] = error

order = []
def visit(name):
    if name in order: return
    if isinstance(structs[name], Exception): raise structs[name]
    for typ, _, _, _ in structs[name]:
        if typ in structs: visit(typ)
    order.append(name)
visit('GameSession')
index = {n: i for i, n in enumerate(order)}

def ctype(name):
    # anonymous inner structs have no C name: reach them through the parent
    return name

out = []
out.append('/* Generated from the session headers (see game_session_schema.h);')
out.append('   test_game_session_schema checks that every byte is covered. */')
out.append('#include "game_session_schema.h"')
out.append('')
out.append('#include <stddef.h>')
out.append('')
paths = {'GameSession': 'GameSession'}
# For anonymous structs, element expression goes through the parent type.
anon_expr = {}
for name in order:
    for typ, fname, dims, inner in structs[name]:
        if inner:
            anon_expr[typ] = (name, fname, len(dims))

def elem_expr(owner, fname, ndims):
    return '((%s *)0)->%s%s' % (owner_ctype(owner), fname, '[0]' * ndims)

def owner_ctype(owner):
    return 'struct ' + owner if owner in tagged else owner

out.append('#define SCHEMA_FIELD(T, f, e, k) { #f, (uint32_t)offsetof(T, f), \\')
out.append('    (uint32_t)sizeof(e), (uint32_t)(sizeof(((T *)0)->f) / sizeof(e)), \\')
out.append('    (uint32_t)__alignof__(e), k }')
out.append('')
for name in order:
    T = owner_ctype(name)
    out.append('static const GameSessionSchemaField k_fields_%s[] = {' % name)
    for typ, fname, dims, inner in structs[name]:
        e = elem_expr(name, fname, len(dims))
        k = index[typ] if typ in structs else -1
        out.append('    SCHEMA_FIELD(%s, %s, %s, %d),' % (T, fname, e, k))
    out.append('};')
out.append('')
out.append('const GameSessionSchemaType game_session_schema_types[] = {')
for name in order:
    T = owner_ctype(name)
    out.append('    { "%s", (uint32_t)sizeof(%s), k_fields_%s,' % (name, T, name))
    out.append('      (uint32_t)(sizeof(k_fields_%s) / sizeof(k_fields_%s[0])) },' % (name, name))
out.append('};')
out.append('')
out.append('const uint32_t game_session_schema_type_count =')
out.append('    (uint32_t)(sizeof(game_session_schema_types) /')
out.append('               sizeof(game_session_schema_types[0]));')
out.append('const uint32_t game_session_schema_root = %d;' % index['GameSession'])
sys.stdout.write('\n'.join(out) + '\n')
sys.stderr.write('types %d fields %d\n' % (len(order), sum(len(structs[n]) for n in order)))
