#! /bin/bash
##

die() {
	echo "ERROR: $*" >&2
	exit 1
}

test -n "$SAT_GIT" || die 'Not set [$SAT_GIT]'

base=`cat $SAT_GIT/VERSION_PREFIX`
if test `git tag | grep $base`;then
	oldbuild=`git tag | grep $base | head -n 1 | cut -d '-' -f2`
	build=$((oldbuild+1))
else
	build=0
fi

t=$base-$build
git tag $t
git push origin $t

