# gbdkjs-example-boilerplate

> GBDKJS Example Boilerplate

![Screenshot](screenshot.png?raw=true)

## Dependencies

- [Emscripten](http://kripken.github.io/emscripten-site/)
- [GBDK](http://gbdk.sourceforge.net/) ([Mac Build](http://www.rpgmaker.it/proflame/gbdk.zip))

Install both and make sure `emcc` and `lcc` are in your `$PATH`.

## Build

```shell
git clone git@github.com:gbdkjs/gbdkjs-example-boilerplate.git;
cd gbdkjs-example-boilerplate;
npm install;
```

### Game Boy ROM

```shell
make rom;
open build/gb/game.gb;
```

### Emscripten 

```shell
make web;
live-server build/web;
```
