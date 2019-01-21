
EXAMPLES := examples/


glucose:  $(BIN)glucose-3.0
glucose_release: $(BIN)glucose-3.0_release


$(call REQUIRE-DIR, $(BIN)glucose-3.0)
$(call REQUIRE-DIR, $(BIN)glucose-3.0_release)

# Glucose 3.0
$(BIN)glucose-3.0: default FORCE
	$(call cmd-make, clean, $(EXAMPLES)solvers/glucose-3.0/core)
	$(call cmd-make, , $(EXAMPLES)solvers/glucose-3.0/core)
	$(call cmd-cp, $@, $(EXAMPLES)solvers/glucose-3.0/core/glucose)

FORCE:
$(BIN)glucose-3.0_release: default FORCE
	$(call cmd-make, clean, $(EXAMPLES)solvers/glucose-3.0/core)
	$(call cmd-make, rs, $(EXAMPLES)solvers/glucose-3.0/core)
	$(call cmd-cp, $@, $(EXAMPLES)solvers/glucose-3.0/core/glucose_release)

clean-solvers:
	$(call cmd-make, clean, $(EXAMPLES)solvers/glucose-3.0/core)


FORCE:

.PHONY: solvers FORCE
