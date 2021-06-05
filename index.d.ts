declare module 'source-highlight' {
    interface HighlightBuilderError extends Error {
        filename: string;
        line: number;
    }

    interface ParserError extends Error {
        additional: number;
        filename: string;
        line: number;
    }

    class SourceHighlight {
        constructor();
        public initialize(): void;
        public checkLangDef(langFile: string): void;
        public checkOutLangDef(outLangDef: string): boolean;
        public highlight(input: string, output: string, inputLang: string): void;
        public highlight(input: Buffer, inputLang: string, inputFileName: string): Buffer;
        public setDataDir(dataDir: string): void;
        public setStyleFile(styleFile: string): void;
        public setStyleCssFile(cssFile: string): void;
        public setStyleDefaultFile(styleDefaultFile: string): void;
        public setTitle(title: string): void;
        public setInputLang(inputLang: string): void;
        public setCss(css: string): void;
        public setHeaderFileName(h: string): void;
        public setFooterFileName(f: string): void;
        public setOutputDir(outputDir: string): void;
    }
}