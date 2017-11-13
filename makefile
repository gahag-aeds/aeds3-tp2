SrcDir       = src
LibDir       = $(SrcDir)/lib*
ExactDir     = $(SrcDir)/exact
HeurDir = $(SrcDir)/heuristic

find-c = $(shell find $(1) -name '*.c')

Lib-CompilationUnits = $(call find-c,$(LibDir))

Exact-OutputFile = exato
Exact-CompilationUnits = $(Lib-CompilationUnits) $(call find-c,$(ExactDir))

Heur-OutputFile = heuristica
Heur-CompilationUnits = $(Lib-CompilationUnits) $(call find-c,$(HeurDir))


Build    = gcc
Standard = -std=c99 -pedantic
Libs     = -lm
Warnings = -Wall -Wextra -Werror
Optimize = -O2 -flto

BuildFlags  = $(Warnings)       \
              $(Standard)       \
              $(Libs)           \
              $(Optimize)       \
              -I $(SrcDir)      \
              -o $(1)

DebugFlags = -g

ReleaseFlags = -DNDEBUG



all: release-exact release-heuristic


build-exact: $(SrcDir)
	@$(Build) $(call BuildFlags,$(Exact-OutputFile)) $(DebugFlags) $(Exact-CompilationUnits)

build-heuristic: $(SrcDir)
	@$(Build) $(call BuildFlags,$(Heur-OutputFile)) $(DebugFlags) $(Heur-CompilationUnits)


release-exact: $(SrcDir)
	@$(Build) $(call BuildFlags,$(Exact-OutputFile)) $(ReleaseFlags) $(Exact-CompilationUnits)

release-heuristic: $(SrcDir)
	@$(Build) $(call BuildFlags,$(Heur-OutputFile)) $(ReleaseFlags) $(Heur-CompilationUnits)


clean:
	rm $(Exact-OutputFile)
	rm $(Heur-OutputFile)
