"use strict";
var SourceHighlight = require("../build/Release/node-source-highlight").SourceHighlight;
const path = require("path");
const fs = require("fs");

try {
  const packageDir = path.resolve(__dirname, "../");
  const sourceHighlight = new SourceHighlight("html.outlang");

  sourceHighlight.checkLangDef("typescript.lang");
  sourceHighlight.checkOutLangDef("html.outlang");

  sourceHighlight.highlight(
    path.resolve(__dirname, 'source.ts'),
    path.resolve(__dirname, 'source.html'),
    "typescript.lang",
  );
} catch (e) {
  console.log(e);
}