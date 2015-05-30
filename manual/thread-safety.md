---
layout: doc
title: Thread Safety
order: 110
description: Function calls are not thread-safe as a design choice.
---

Function calls are *not* thread-safe as a design choice. Functions require a lock when they are called in parallel to generator functions like `BKContextGenerate`. Assuming that the audio data is generated in its own thread provided by an audio framework (e.g. [SDL](https://www.libsdl.org)) and [tracks](../generating-sound/), [instruments](../instruments/) or other objects are controlled by the main thread; this would require a lock that wraps the library function calls.

 In case of SDL, which provides lock functions for this purpose, library function calls in the main thread should be wrapped between `SDL_LockAudioDevice` and `SDL_UnlockAudioDevice`.
