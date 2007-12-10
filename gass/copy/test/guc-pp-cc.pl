#! /usr/bin/env perl

# 
# Copyright 1999-2006 University of Chicago
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
# http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 


use strict;
use Test::Harness;
use Cwd;
use Getopt::Long;
require 5.005;
use File::Temp qw/ tempfile tempdir /;

push(@INC, $ENV{GLOBUS_LOCATION} . "/test/globus_gridftp_server_test");

require "gfs_common.pl";

my @tests;
my @todo;

my $globus_location = $ENV{GLOBUS_LOCATION};

#$Test::Harness::verbose = 1;

my $runserver;
my $runwuserver;
my $nogsi;
my $server_pid;
my $server_cs;
my $subject;

GetOptions('nogsi' => \$nogsi);


my @dc_opts;

my @proto;

if(defined($nogsi))
{
    push(@dc_opts, "");
    push(@proto, "ftp://");
}
else
{
    $subject = gfs_setup_security_env();

    push(@dc_opts, "-nodcau -subject \"$subject\"");
    push(@dc_opts, "-subject \"$subject\"");
    push(@dc_opts, "-dcsafe -subject \"$subject\"");
    push(@dc_opts, "-dcpriv -subject \"$subject\"");

    push(@proto, "gsiftp://");
}

my @concur;
push(@concur, "");
for(my $i = 1; $i < 32; $i++)
{
    push(@concur, "-cc $i");
}
# tests here
#$server_pid,$server_cs = gfs_setup_server_basic();
$server_pid,$server_cs = gfs_setup_server_fe();
# setup dirs
my $work_dir = tempdir( CLEANUP => 1);
mkdir("$work_dir/etc");

system("cp -rL $globus_location/* $work_dir/etc/ >/dev/null 2>&1");

foreach(@proto)
{
    my $p=$_;
    my $src_url = "$p"."$server_cs"."$work_dir/etc/";
    my $dst_url = "$p"."$server_cs"."$work_dir/etc2/";

    foreach(@dc_opts)
    {
        my $dc_opt=$_;

        foreach(@concur)
        {
            my $cc=$_;
            my $cmd = "globus-url-copy $cc $dc_opt -cd -pp -r $src_url $dst_url";

            push(@tests, $cmd);
        }
    }
}

my $cnt=0;
foreach(@tests)
{
    &run_guc_test("$_");
    system("rm -rf $work_dir/etc2/");
    $cnt++;
}


sub run_guc_test()
{
    my $cmd = shift;
        print "$cmd\n";
        my $rc = system($cmd);
        if($rc != 0)
        {
            gfs_cleanup();
            print "ERROR\n";
            exit 1;
        }
        $rc = system("diff -r $work_dir/etc/ $work_dir/etc2/");
        if($rc != 0)
        {
            gfs_cleanup();
            print "ERROR\n";
            exit 1;
        }
}
