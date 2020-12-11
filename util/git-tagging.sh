#! /bin/bash
##

die() {
	echo "ERROR: $*" >&2
	exit 1
}
ok() {
	echo "INFO: $*" >&2
	exit 0
}

test -n "$SAT_GIT" || die 'Not set [$SAT_GIT]'

base=$(cat $SAT_GIT/VERSION_PREFIX) || die "Unable to get base version"
ltag=$(git tag | grep $base | tail -n 1)
ctag=$(git describe --tags)

test "$ltag" = "$ctag" && ok "Commit already tagged $ltag"

if test -n "$ltag";then
	oldbuild=$(echo $ltag | cut -d '-' -f2)
	build=$((oldbuild+1))
else
	build=0
fi

t=$base-$build
git tag $t || die "Unable to tag $t locally"
git push origin $t || die "Unable to push tag $t to origin"

