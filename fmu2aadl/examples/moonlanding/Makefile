all: moonlanding_fmu.aadl check_aadl code_gen

moonlanding_fmu.aadl:
	fmu2aadl ../../../models/MoonLanding/MoonLanding.fmu

code_gen: moonlanding_fmu.aadl
	ocarina -aadlv2 -y -g polyorb_hi_c moonlanding.aadl

check_aadl: moonlanding_fmu.aadl
	ocarina -aadlv2 -y moonlanding.aadl

clean:
	-rm -rf *~

distclean: clean
	-rm -rf moonlanding_sys_impl
