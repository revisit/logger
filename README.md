# logger
A logging library for Revisit.

## CPP

The `logger` C++ library requires [`JSON for Modern C++`](https://github.com/nlohmann/json). On a mac you can install with `brew`:

```bash
brew install nlohmann_json
```

### File Format

```
name: string
duration: float, req.
timeStep: float, req.
loop: boolean
follow: object index

objects: list, req.
    name: string, req. unique
    type: enumeration, req.
    material:
        color: vec4 float
        metallic: float
        roughness: float
    static: boolean
    translation: vec3 float
    rotation: vec4 float
    scale: vec3 float
    children: list (child positions relative to parent)
        name: string, req.
        type: enumeration, req.
        translation: vec3 float
        rotation: vec4 float
        scale: vec3 float
        children: recursive

frames: list, req. length is (duration / timeStep + 1)
    <name from above (not nested)>:
        t: vec3 float
        r: vec4 float
        s: vec3 float
    .
    .
    .
    <name from above (not nested)>: same as previous
```
