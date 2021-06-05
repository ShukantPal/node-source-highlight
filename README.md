# node-source-highlight

[GNU source-highlight](https://www.gnu.org/software/src-highlite/) is a library to highlight source code in several different languages and output
formats. This package provides Node.js bindings to the C++ library; currently, it requires you to have
the library preinstalled.

## Installation :package:

```bash
npm install --save source-highlight
```

## API Documentation - SourceHighlight

```typescript
import { SourceHighlight } from 'source-highlight';
```

source-highlight@1.0.0 exports just the `SourceHighlight` class. The API documentation for the GNU source-highlight
can be found [here](https://www.gnu.org/software/src-highlite/api/index.html). The methods of `SourceHighlight` provided
by this package are enlisted below.

### Constructor

```typescript
constructor(outLangDef: string)
```

Create a `SourceHighlight` instance that will output into the format specified, e.g. `html.outlang`.

### highlight

```typescript
highlight(input: string, output: string, inputLang: string): void
```

Highlight the input file and write into the output file. `inputLang` is the name of the language
definition file you want to use. (This cannot be a path, e.g. `html.lang` is valid not `/path/to/html.lang`)

```typescript
highlight(input: Buffer, inputLang: string, inputFileName: string): Buffer
```

Highlight the source code in the UTF-8 buffer using the language definition file `inputLang` (again only a
filename in the data directory, not a path). You can provide `inputFileName` optionally OR pass a blank string.

### checkLangDef

```typescript
checkLangDef(langFile: string): void
```

Check if the language definition file (in the data directory) is valid. It will throw an error if it is invalid.

### checkOutLangDef

```typescript
checkOutLangDef(outLangFile: string): void
```
Check if the output format specification file (in the data directory) is valid. It will throw an error if it is invalid.

### setDataDir

```typescript
setDataDir(dataDir: string): void
```
Set the data directory. By default, this will be a directory with all the language definition files and output formats that ship with GNU source-highlight.

### setStyleFile

```typescript
setStyleFile(styleFile: string): void
```

Set the style file.

### setStyleCssFile

```typescript
setStyleCssFile(cssFile: string): void
```

Use a CSS style file.

### setStyleDefaultFile

```typescript
setStyleDefaultFile(styleFile: string): void
```

Set the default style file.

### setTitle

```typescript
setTitle(title: string): void
```

### setInputLang

```typescript
setInputLang(inputLang: string): void
```

Set the input language to use when it can't be inferred.

### setCss

```typescript
setCss(css: string): void
```

### setHeaderFileName

```typescript
setHeaderFileName(headerFileName: string): void
```

Set the header file to be prepended to the output document.

### setFooterFileName

```typescript
setFooterFileName(footerFileName: string): void
```

Set the footer file to be appended to the output document.

### setOutputDir

```typescript
setOutputDir(outputDir: string): void
```