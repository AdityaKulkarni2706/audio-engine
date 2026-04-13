## C++ Audio Processing Engine

A real-time-capable digital audio processing engine written in modern C++ (C++17). This project implements a modular architecture for reading, manipulating, and writing audio files using custom digital signal processing (DSP) algorithms.

---

## Level 1: The Bird's Eye View (High-Level Flow)

At its highest level of abstraction, this engine acts as an automated studio pipeline. It ingests raw audio, breaks it down into manageable components, routes it through an effects processor, and reconstructs the final track.

Here is the life cycle of an audio signal moving through the engine:

```
 ┌──────────────┐     ┌──────────────┐     ┌──────────────┐
 │  input.wav   │ ──> │ AudioFileIO  │ ──> │ AudioClip    │ (Interleaved Stereo)
 └──────────────┘     └──────────────┘     └──────┬───────┘
                                                  │
                                            [Deinterleave]
                                                  │
                      ┌───────────────────────────┴───────────────────────────┐
                      ▼                                                       ▼
               Mono Clip (Left)                                        Mono Clip (Right)
                      │                                                       │
              [SplitIntoBlocks]                                       [SplitIntoBlocks]
                      │                                                       │
                      ▼                                                       ▼
 ┌────────────────────────────────────────┐             ┌────────────────────────────────────────┐
 │ AudioProcessor (Left)                  │             │ AudioProcessor (Right)                 │
 │  ├─► [Block 1] ─► Gain ─► ffDelay ─►   │             │  ├─► [Block 1] ─► Gain ─► ffDelay ─►   │
 │  ├─► [Block 2] ─► Gain ─► ffDelay ─►   │             │  ├─► [Block 2] ─► Gain ─► ffDelay ─►   │
 │  └─► [Block N] ─► Gain ─► ffDelay ─►   │             │  └─► [Block N] ─► Gain ─► ffDelay ─►   │
 └────────────────────┬───────────────────┘             └────────────────────┬───────────────────┘
                      │                                                      │
                [MergeBlocks]                                          [MergeBlocks]
                      │                                                      │
                      ▼                                                      ▼
            Processed Mono (Left)                                  Processed Mono (Right)
                      │                                                      │
                      └───────────────────────────┬──────────────────────────┘
                                                  │
                                            [Interleave]
                                                  │
                                                  ▼
 ┌──────────────┐     ┌──────────────┐     ┌──────────────┐
 │  output.wav  │ ◄── │ AudioFileIO  │ ◄── │ AudioClip    │ (Processed Stereo)
 └──────────────┘     └──────────────┘     └──────────────┘
```
## Level 2: The Engine (Class Architecture)

The engine is designed to use strict object-oriented principles. The DSP logic is decoupled from file I/O and memory management, allowing effects to be easily swapped, chained, and tested.

Core Data Structures:
1) AudioClip: Represents an entire audio file in memory. Contains raw floating-point samples, sample rate, and channel metadata.

2) AudioBlock: Represents a small, fixed-size chunk of an AudioClip (e.g., 512 samples). Processing audio in blocks mimics real-time hardware constraints and optimizes CPU cache usage.

Routing and Utility:
1) interleave: combines audio data of multiple channels into a singular array for writing.
2) deinterleave: splits interleaved audio data into a vector of multiple audio clips representing their own channels.
3) splitIntoBlocks: breaks an audio clip into a vector of blocks of fixed length called as buffer length. 
4) mergeBlocks: merges a vector of audio blocks into a singular audio clip.
   
Padding is taken care of for 3 and 4.

## The DSP Architecture
```
+-----------------------+        +-----------------------+
|    AudioProcessor     |        |      EffectChain      |
|-----------------------|        |-----------------------|
| - effectChain         |------->| - std::vector<Effect> |
| + processBlock(block) |        | + process(block)      |
| + addEffect(effect)   |        | + addEffect(effect)   |
+-----------|-----------+        +-----------|-----------+
            |                                |
            | modifies                       | contains
            v                                v
+-----------------------+        +-----------------------+
|      AudioBlock       |<=======|   Effect (Base Class) |
|-----------------------| alters |-----------------------|
| - vector<float>       |        | + process(block) = 0  |
| - numFrames           |        +-----------|-----------+
+-----------------------+                   / \ inherits
                                           /   \
                 +------------------------+     +------------------------+
                 |          Gain          |     |        ffDelay         |
                 |------------------------|     |------------------------|
                 | - gainAmount           |     | - CircularBuffer       |
                 | + process(block)       |     | - delayTime, feedback  |
                 +------------------------+     +------------|-----------+
                                                             | uses
                                                             v
                                                +------------------------+
                                                |     CircularBuffer     |
                                                |------------------------|
                                                | + write(sample)        |
                                                | + read(delayAmount)    |
                                                +------------------------+
```

