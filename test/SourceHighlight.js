"use strict";
var SourceHighlight = require("../build/Release/node-source-highlight").SourceHighlight;
const path = require("path");
const fs = require("fs");

try {
  const packageDir = path.resolve(__dirname, "../");
  const sourceHighlight = new SourceHighlight("html.outlang");

  sourceHighlight.checkLangDef("c_string.lang");
  sourceHighlight.checkOutLangDef("html.outlang");

  const out = sourceHighlight.highlight(Buffer.from(`"This is a test"`), "c_string.lang", "");

  console.log(out);
} catch (e) {
  console.log(e);
}