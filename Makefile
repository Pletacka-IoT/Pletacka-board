.PHONY: build

build:
	mkdir ./hw/export
	kikit fab jlcpcb --assembly --forceSMD --schematic ./hw/Pletacka-board.sch ./hw/Pletacka-board.kicad_pcb ./hw/export

