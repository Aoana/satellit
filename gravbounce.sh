#! /bin/sh
##
## gravbounce.sh --
##
##	Script for the gravbounce game.
##
##	Preparation;
##
##	# Install the following packages
##		sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev \
##		doxygen libconfig-dev
##
##
##	Build Gravbounce;
##
##		gravbounce build
##
##	Start and stop Gravbounce;
##
##		gravbounce start
##		gravbounce stop
##
## Commands;
##

prg=$(basename $0)
dir=$(dirname $0); dir=$(readlink -f $dir)
me=$dir/$prg
tmp=/tmp/${prg}_$$
sshopt='-q -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no'

die() {
	echo "ERROR: $*" >&2
	rm -rf $tmp
	exit 1
}
help() {
	grep '^##' $0 | cut -c3-
	rm -rf $tmp
	exit 0
}
test -n "$1" || help
echo "$1" | grep -qi "^help\|-h" && help

test -n "$GB_WS" || die 'Not set [$GB_WS]'
test -n "$GB_GIT" || die 'Not set [$GB_GIT]'

##	build [--clean]
##		Compiles gravbounce
##
cmd_build() {

	cd $GB_GIT
	if test "$__clean" = "yes"; then
		make clean
	fi
	make
}

##	start
##		Starts gravbounce
##
cmd_start() {

	gravbounce=$GB_WS/gravbounce
	test -x "$gravbounce" || die 'No executable $gravbounce'
	$gravbounce

}

##	generate_doc
##		Generate source documentation
##
cmd_generate_doc() {

	doxygen $GB_GIT/doc/doc.conf

}

# Get the command
cmd=$1
shift
grep -q "^cmd_$cmd()" $0 $hook || die "Invalid command [$cmd]"

while echo "$1" | grep -q '^--'; do
	if echo $1 | grep -q =; then
		o=$(echo "$1" | cut -d= -f1 | sed -e 's,-,_,g')
		v=$(echo "$1" | cut -d= -f2-)
		eval "$o=\"$v\""
	else
		o=$(echo "$1" | sed -e 's,-,_,g')
		eval "$o=yes"
	fi
	shift
done
unset o v
long_opts=`set | grep '^__' | cut -d= -f1`

# Execute command
trap "die Interrupted" INT TERM
cmd_$cmd "$@"
status=$?
rm -rf $tmp
exit $status
