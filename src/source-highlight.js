const lib = require('../build/Release/node-source-highlight');

const highlight = new lib.SourceHighlight();

highlight.initialize();

const src = Buffer.from(`
function test() {
  console.log('HELLO_WORLD');
}
`);

console.log(highlight.highlight(src, "javascript.lang", ""));