---
layout: doc
title: Thread Safety
order: 110
description: Function calls are not thread-safe as a design choice. In some situations, function calls require a lock, which is the case when the same objects are used in different threads.
---

Function calls are *not* thread-safe as a design choice. In some situations, function calls require a lock, which is the case when the same objects are used in different threads. Assuming that the audio data is generated in its own thread provided by an audio framework (e.g. [SDL](https://www.libsdl.org)) and the objects are controlled by the main thread; this would require a lock that wraps the library function calls.

 In case of SDL, which provides lock functions for this purpose, library function calls in the main thread should be wrapped between `SDL_LockAudioDevice` and `SDL_UnlockAudioDevice`.
