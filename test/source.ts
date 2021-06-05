/// <reference types="node" />

const EventEmitter = require("events");

const mix = (mixin: any) => (_class: typeof Sampler) => {

}

module Browser {
    export interface EventListener {

    }
}

@mix(EventEmitter)
class Sampler<T extends Record<string, number>> {
    constructor() {}

    isEmpty(t: number): boolean {
        return true
    }

    get length(): number {
        return (0 + 24);
    }
    set length(value: number) {
        throw new Error('This program has not been implemented!')
    }

    operate(fn: (v: number) => void): number {
        return 0;
    }

    clone(): Sampler<T> {
        return new Sampler<T>();
    }
}

type SamplerResult<T extends number = number> = T;

const results: SamplerResult = new Sampler().operate((v: number) => {
    console.log(v);
});

function main(args: [string, SamplerResult], seed?: SamplerResult<Number>): boolean {

}