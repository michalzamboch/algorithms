add_rules("mode.debug", "mode.release")

set_languages("c++17")
set_optimize("faster")

target("bipartit_graph_algorithm")
    set_kind("binary")
    add_files("src/*.cpp")
    
    after_build(function (target)
        print("\nbinary: %s", target:name())
        print("target: %s", target:targetfile())
        os.cp("traces/*.txt", target:targetdir())
    end)
