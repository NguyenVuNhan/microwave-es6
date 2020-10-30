SUBDIRS = src test

all: src

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	$(foreach DIR, $(SUBDIRS), $(MAKE) -C $(DIR) $@;)

.PHONY: all $(SUBDIRS)
