# Verse #

This repository contains code by Eskil Steenberg, with some small
changes by me, Phillip Warren. My first goal for this repository
is to port LoqAirou (3D modelling tool) to the browser via emscripten.

I am interested in this software because:
    
  * It is innovative and potentially useful if packaged and maintained
  * It is well architectured, easy to compile (portable c).
  * Eskil's ideas are interesting. Some of his links on quelsolaar.com are bitrotting and it would
    be a shame to lose his creative work to bit rot.
    
Please see [this Wiki page](https://github.com/Gages/verse_apps/wiki/Loq-Airou-Demonstrations) for links to video demonstrations of LoqAirou.
    
## Compiling ##

[![Build Status](https://travis-ci.org/Gages/verse_apps.svg?branch=master)](https://travis-ci.org/Gages/verse_apps)

I've added a basic build system using [tup](http://gittup.org/tup/). Look in the `artefact`
directory, which contains all the build scripts. To compile, follow the instructions to install
tup if you don't have it already, and then run these two commands from the top level of the repository:

```
    tup variant tupconf/default.config
    tup
```
 
 The outputs of the build are in the folder `build-default/artefacts/`.

### Caveats ###

* SDL (v 1.2) and OpenGL are required. I plan to move the dependency to SDL2 soon.
* I've currently only run this on my Arch Linux laptop. Please let me know if you have problems on any other Linux distribution.
* I hope to add Windows, Mac, and Emscripten builds soon, as well as binary downloads, once I have a verse server implementation.

## Origin ##

The original source of this repository was:

 * A zip file  http://quelsolaar.com/files/verse_apps.zip, with sha1 hash `97fac3d14419935063151d1b404165bcb7db8338`. Future people might prefer to download from the [archive.org mirror](http://web.archive.org/web/20160417060951/http://www.quelsolaar.com/files/verse_apps.zip).
 * A copy of the verse library and server from the [blender-staging git repository](https://developer.blender.org/diffusion/BS/browse/master/extern/verse/dist;0bd7934be731aba65680c7fe59f2d89a06391899), from a commit in 2009. 

Please see [quelsolaar.com](http://quelsolaar.com/) for more information on the origin of this code and the purpose of the apps contained within.

## Links to Eskil's Old and New stuff ##

Here are some links to relevant things. These links provide further documentation, for now.

Older things:
* [QuelSolaar.com](http://www.quelsolaar.com/verse/index.html) contains many interesting things.
* [Verse Sourceforge.](http://verse.sourceforge.net/index-before-blender-2.3.html) The top-level index seems to redirect to a bitrotted link on blender.org. Alternatively try the [archive.org mirror](http://web.archive.org/web/20031014224210/http://verse.sourceforge.net/) circa 2003.
* [verse.blender.org](http://web.archive.org/web/20120316140903/http://verse.blender.org/) circa March 2012. I've linked to archive.org since the actual site seems to have disappeared.
* [uni-verse.org](http://web.archive.org/web/20111121011435/http://www.uni-verse.org/Uni-verse-Home.72.0.html). This domain has changed owner. The link goes to the archived version from November 2011.

New things:
* [Ekil's twitter feed](https://twitter.com/quelsolaar)
* [Eskil's new blog](http://unravel.org/)
  
## License ##

The .zip file mentioned above doesn't contain explicit licenses. It is
my intention to contact Eskil to ask him about licenses and include
them explicitly here.

However, on quelsolaar.com Eskil says:

 * Quel Solaar source code is licensed under [OpenBSD](http://www.quelsolaar.com/quelsolaar/downloads.html) or [FreeBSD](http://www.quelsolaar.com/quel_solaar/features.html) License.
 * [Seduce][seduce], [Betray][betray], [Persaude][persuade], [Enough][enough] are licensed under FreeBSD License.

Currently the licenses for the other source code components are unknown.

[betray]:   http://www.quelsolaar.com/technology/betray.html
[seduce]:   http://www.quelsolaar.com/technology/seduce.html
[persuade]: http://www.quelsolaar.com/technology/persuade.html
[enough]:   http://www.quelsolaar.com/technology/enough.html

## Other Files ##

There are other zip files distributed at quelsolaar and gamepipeline.org which contain source code that may contain newer versions of
verse, new features, and new applications that are open source. So far I've found:

* Adri Om, a data viewer, and advance, a profiling data collection library. http://quelsolaar.com/advance.zip
* Confuse, a procedural character animation editor and library. http://quelsolaar.com/animator.zip
* Quel Solaar libraries at [gamepipeline.org](http://gamepipeline.org/) , FreeBSD Licenced. http://www.quelsolaar.com/mergesource.zip
* [verse 2.0 on github](https://github.com/verse/verse). I chose not to use this for now, as I don't understand the verse protocol and can't say if it is compatible with the client applications here.

## Roadmap ##

* [ ] Change SDL dependency to SDL2.
* [ ] Modify code to remove all compiler warnings.
* [ ] Integrate additional code into this repository, first in seperate folders, later without duplications. (After a test suite exists)
* [ ] Make some kind of test system and continuous building to enable faster development and contributions.
* [ ] Add builds for other platforms, including the browser.
* [ ] Run some static analysis tools on the code to learn more about it and increase robustness.
* [ ] Add documentation including examples
