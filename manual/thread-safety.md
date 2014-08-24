---
layout: doc
title: Thread safety
order: 40
---

Function calls are *not* thread-safe by design choice. In some situations, function calls require a lock. Which is the case when the libary is controlled by different threads. Assuming that the audio is generated in its own working thread (*generator thread*) provided by an audio framework (e.g. [SDL](https://www.libsdl.org)). But the track objects are controlled by an user interface which is running, for example, on the main thread (*controlling thread*). This situation requires a lock, which wraps the library function calls.

 In case of SDL, which provides lock functions for this purpose, library function calls in the controlling thread have to be wrapped between `SDL_LockAudioDevice` and `SDL_UnlockAudioDevice` calls.
