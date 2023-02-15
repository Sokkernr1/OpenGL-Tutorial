cd cmake-build-debug/
rm -rf conanBuild/
mkdir conanBuild && cd conanBuild
conan install ../.. --build
