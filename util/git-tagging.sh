#! /bin/bash
##

die() {
	echo "ERROR: $*" >&2
	exit 1
}

test -n "$SAT_GIT" || die 'Not set [$SAT_GIT]'

base=`cat $SAT_GIT/VERSION_PREFIX`
git tag | grep $base
if test $?;then
	oldbuild=`git tag | grep $base | tail -n 1 | cut -d '-' -f2`
	build=$((oldbuild+1))
else
	build=0
fi

t=$base-$build
git tag $t
git push origin $t

