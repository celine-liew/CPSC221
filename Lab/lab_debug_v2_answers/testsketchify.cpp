#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "sketchify.h"
#include "cs221util/PNG.h"

using namespace cs221util;


TEST_CASE("test ubc icon","[sketchify][white background]"){
	sketchify("given_imgs/in.png", "out.png");
	PNG expIm, outIm;
	expIm.readFromFile("given_imgs/out_ubc.png");
	outIm.readFromFile("out.png");
    REQUIRE(outIm==expIm);
}

TEST_CASE("test icics","[sketchify][building]"){
	sketchify("given_imgs/in_02.png", "out_icics.png");
	PNG expIm, outIm;
	expIm.readFromFile("given_imgs/out_icics.png");
	outIm.readFromFile("out_icics.png");
	REQUIRE(outIm==expIm);
}
