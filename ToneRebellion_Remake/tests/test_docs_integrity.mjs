import assert from 'node:assert/strict';
import { existsSync, readFileSync, readdirSync } from 'node:fs';
import path from 'node:path';
import test from 'node:test';
import { fileURLToPath } from 'node:url';

const testDirectory = path.dirname(fileURLToPath(import.meta.url));
const repoRoot = path.resolve(testDirectory, '../..');
const markdownFiles = [];

function collectMarkdown(directory) {
    for (const entry of readdirSync(directory, { withFileTypes: true })) {
        const fullPath = path.join(directory, entry.name);
        if (entry.isDirectory()) {
            if (entry.name !== '.git' && entry.name !== 'build' && entry.name !== 'node_modules') {
                collectMarkdown(fullPath);
            }
        } else if (entry.isFile() && entry.name.endsWith('.md')) {
            markdownFiles.push(fullPath);
        }
    }
}

collectMarkdown(repoRoot);

const decoder = new TextDecoder('utf-8', { fatal: true });
const documents = [];
const invalidUtf8Files = [];
for (const filePath of markdownFiles) {
    const relativePath = path.relative(repoRoot, filePath);
    const bytes = readFileSync(filePath);
    try {
        documents.push({ filePath, relativePath, text: decoder.decode(bytes) });
    } catch {
        invalidUtf8Files.push(relativePath);
        documents.push({ filePath, relativePath, text: bytes.toString('utf8') });
    }
}

function checkEncoding() {
    const errors = invalidUtf8Files.map((file) => `${file}: invalid UTF-8`);
    const mojibake = /(?:Ã[\u00a0-\u00ff]|Â[\u00a0-\u00ff]|â€.|ï»¿)/u;
    for (const document of documents) {
        if (document.text.includes('\uFFFD') || mojibake.test(document.text)) {
            errors.push(document.relativePath);
        }
    }
    return errors;
}

function checkLocalLinks() {
    const errors = [];
    const linkPattern = /\[[^\]]*\]\((<[^>\r\n]+>|[^)\s]+)(?:\s+"[^"]*")?\)/g;
    for (const document of documents) {
        for (const match of document.text.matchAll(linkPattern)) {
            let target = match[1];
            if (target.startsWith('<')) target = target.slice(1, -1);
            if (/^[a-z][a-z\d+.-]*:/i.test(target) || target.startsWith('#')) continue;

            const localTarget = target.split(/[?#]/, 1)[0];
            if (!localTarget) continue;
            let decodedTarget;
            try {
                decodedTarget = decodeURIComponent(localTarget);
            } catch {
                errors.push(`${document.relativePath}: invalid URL escape in ${target}`);
                continue;
            }

            const resolved = path.resolve(path.dirname(document.filePath), decodedTarget);
            if (!existsSync(resolved)) errors.push(`${document.relativePath}: missing ${target}`);
        }
    }
    return errors;
}

function checkFunctionReferences() {
    const indexPath = path.join(repoRoot, 'index.jsonl');
    const knownFunctions = new Set();
    for (const line of readFileSync(indexPath, 'utf8').split(/\r?\n/)) {
        if (!line) continue;
        const entry = JSON.parse(line);
        if (typeof entry.name === 'string') knownFunctions.add(entry.name);
    }

    const errors = [];
    const functionPattern = /\bFUN_[0-9a-fA-F]{8}\b/g;
    for (const document of documents) {
        for (const match of document.text.matchAll(functionPattern)) {
            if (!knownFunctions.has(match[0])) {
                errors.push(`${document.relativePath}: ${match[0]} is absent from index.jsonl`);
            }
        }
    }
    return errors;
}

test('Markdown is valid UTF-8 and has no common encoding-corruption markers', () => {
    assert.ok(documents.length > 0, 'no Markdown documents found');
    assert.deepEqual(checkEncoding(), []);
});

test('local Markdown links point to existing files or directories', () => {
    assert.deepEqual(checkLocalLinks(), []);
});

test('documented FUN_* references exist in the function index', () => {
    assert.deepEqual(checkFunctionReferences(), []);
});
