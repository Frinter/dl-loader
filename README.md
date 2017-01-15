# dl-reloader

This is a relatively low-level code reloading layer. It operates by loading **shared libraries** at run-time, and the intent is that it should make very few assumptions otherwise. A **module** is what I call the thing that operates on a shared library. There are a few standard functions that a module must provide (mostly for initialization purposes), and there is an interface for loading functions from other modules. This probably only works with C++ on Windows at the moment.

## Modules

A module loads and tracks a shared library. A module can be instructed to unload or replace the shared library.

## Shared Libraries

A shared library for a module must provide the following functions:
- `void onModuleLoad(void *params)`
  * `params` is intended to be cast as the struct in [src/loadparameters.hh](src/loadparameters.hh), which includes a `void *` to data that was passed from the previous version of the library for the module (if any). This data is controlled by the library and can be anything.
  * This function is called when the module is loaded. This includes loading the first time as well as when a replacement is loaded.
- `void *exportModuleDate(void *params)`
  * This function is called when the module is about to be unloaded. It provides an opportunity to save any internal data that the module is tracking and have it passed to the replacement library. `params` in this call will be `NULL`.
