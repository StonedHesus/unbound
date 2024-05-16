const std = @import("std");

pub fn build(b: *std.Build) void {
    
}

//pub fn build(b: *std.build.Builder) void {
//    const target = b.standardTargetOptions(.{});
//    const mode = b.standardReleaseOptions();
//
//    const unbound = b.addStaticLibrary("unbound", null);
//    unbound.setTarget(target);
//    unbound.setBuildMode(mode);
//    unbound.linkLibC();
//    unbound.force_pic = true;
//    unbound.addCSourceFiles(&.{
//        "src/main.c",
//    }, &.{
//        "-Wall",
//        "-W",
//        "-pedantic",
//    });
//}

