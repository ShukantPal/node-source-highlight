"use strict";
var SourceHighlight = require("../build/Release/node-source-highlight").SourceHighlight;
const path = require("path");
const fs = require("fs");

try {
  const packageDir = path.resolve(__dirname, "../");
  const sourceHighlight = new SourceHighlight("html.outlang");

//  sourceHighlight.checkLangDef("typescript.lang");
//  sourceHighlight.checkOutLangDef("html.outlang");

  sourceHighlight.setTitle("TEST");
  sourceHighlight.setHeaderFileName(path.resolve(__dirname, 'header.html'));
  sourceHighlight.setFooterFileName(path.resolve(__dirname, 'footer.html'));
  sourceHighlight.setOutputDir(__dirname);
  sourceHighlight.highlight(
    path.resolve(__dirname, 'source.ts'),
    'source.html',
    "javascript.lang",
  );
} catch (e) {
  console.log(e);
}