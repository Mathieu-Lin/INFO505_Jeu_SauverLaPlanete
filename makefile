# Cible par défaut
all:
	@echo "Choisissez une configuration :"
	@echo "  make gtk    - Pour compiler avec GTK"
	@echo "  make nogtk  - Pour compiler sans GTK"
	@echo "  make clean  - Pour nettoyer les fichiers objets et binaires"

gtk:
	$(MAKE) -f makefile.gtk

nogtk:
	$(MAKE) -f makefile.nogtk

clean:
	$(MAKE) -f makefile.gtk clean
	$(MAKE) -f makefile.nogtk clean
