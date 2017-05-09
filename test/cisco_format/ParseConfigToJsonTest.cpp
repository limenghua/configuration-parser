#include <gtest/gtest.h>
#include "TestUtil.h"

#include <json/json.h>

#include "ConfigureParser/ConfigureParser.h"

static void ParsedConfigResultShouldEqualJson(const std::string & strConfig, const std::string & strJson)
{
	std::string destJsonDoc;
	ParseConfigToJson(strConfig, destJsonDoc);

	Json::Value destJson = CreateJsonFromString(destJsonDoc);
	Json::Value expectDestJson = CreateJsonFromString(strJson);

	EXPECT_EQ(destJson, expectDestJson);
}

TEST(ParseConfigToJsonTest, SimpleConfigure)
{
	std::string strConfig =
R"(
!
version 15.0
!
)";
	std::string strExpectDoc =
R"(
{"version":"15.0"}
)";

	ParsedConfigResultShouldEqualJson(strConfig, strExpectDoc);
}

TEST(ParseConfigToJsonTest, ComplexConfigure)
{
	std::string strConfig =
		R"(
!
version 15.0
hostname example!
interface Loopback0
 ip address 158.4.255.44 255.255.255.255
)";
	std::string strExpectDoc =
		R"(
{
	"version":"15.0",
	"hostname":"example",
	"interfaces":
	[
		{"interface":"Loopback0","ip address":"158.4.255.44 255.255.255.255"}
	]
}
)";

	ParsedConfigResultShouldEqualJson(strConfig, strExpectDoc);
}


static const std::string strConfigContext =
R"(

! Info via SNMP: sysoid=1.3.6.1.4.1.9.1.1,vendor=Cisco,model=ciscoGatewayServer,hostname=ACL_R2
ACL_R2#show run
!
version 15.2
service timestamps debug datetime msec
service timestamps log datetime msec
no service password-encryption!
hostname example
!
boot-start-marker
boot-end-marker
!
enable secret 5 $1$bKsb$u5Xq9gN2xYioRoPNeu3DI/
!
no aaa new-model
!
clock timezone CET 8 0
mmi polling-interval 60
no mmi auto-configure
no mmi pvc
mmi snmp-timeout 180
ip auth-proxy max-login-attempts 5
ip admission max-login-attempts 5
!
no ip domain lookup
ip cef
no ipv6 cef
!
multilink bundle-name authenticated
!
crypto pki token default removal timeout 0
!
!
object-group network netgrp1 
 host 158.4.255.37
 host 158.4.255.38
!
object-group service srvgrp1 
 icmp
 ospf
!
username nb password 0 nb
!
redundancy
!
interface Loopback0
 ip address 158.4.255.44 255.255.255.255
!
interface Ethernet0/0
 ip address 158.4.0.170 255.255.255.252
 ip access-group 1 in
 ip access-group R3toR1 out
!
interface Ethernet0/1
 ip address 158.4.0.173 255.255.255.252
!
interface Ethernet0/2
 no ip address
 shutdown
!
interface Ethernet0/3
 ip address 192.168.240.11 255.255.255.248
!
interface Serial1/0
 ip unnumbered Loopback0
 encapsulation ppp
 serial restart-delay 0
!
interface Serial1/1
 ip address 158.4.255.66 255.255.255.252
 serial restart-delay 0
!
interface Serial1/2
 no ip address
 shutdown
 serial restart-delay 0
!
interface Serial1/3
 no ip address
 shutdown
 serial restart-delay 0
!
!
router eigrp 1
 network 158.4.0.168 0.0.0.3
 network 158.4.0.172 0.0.0.3
!
router ospf 1024
 router-id 1.1.1.8
 network 192.168.240.8 0.0.0.7 area 2
!
ip forward-protocol nd
!
!
no ip http server
no ip http secure-server
!
ip access-list standard R1toR3
 deny   158.4.233.29
 permit any
!
ip access-list extended R3toR1
 deny   ip 158.4.255.32 0.0.0.7 any
 permit ip any any
!
access-list 1 permit 158.4.255.37 log
access-list 1 deny   158.4.255.36
access-list 1 deny   158.4.255.38 log

line con 0
 logging synchronous
line aux 0
line vty 0 4
 login local
 transport input all
!
time-range ww
 periodic weekdays 19:15 to 19:16
!
!
end

)";

const std::string strJsonString =

R"(

{
    "childs": [
        {
            "key": "origin",
            "origin": "ACL_R2#show run"
        },
        {
            "key": "origin",
            "origin": "service timestamps debug datetime msec"
        },
        {
            "key": "origin",
            "origin": "service timestamps log datetime msec"
        },
        {
            "key": "origin",
            "origin": "no service password-encryption"
        },
        {
            "key": "origin",
            "origin": "boot-start-marker"
        },
        {
            "key": "origin",
            "origin": "boot-end-marker"
        },
        {
            "key": "origin",
            "origin": "enable secret 5 $1$bKsb$u5Xq9gN2xYioRoPNeu3DI/"
        },
        {
            "key": "origin",
            "origin": "no aaa new-model"
        },
        {
            "key": "origin",
            "origin": "clock timezone CET 8 0"
        },
        {
            "key": "origin",
            "origin": "mmi polling-interval 60"
        },
        {
            "key": "origin",
            "origin": "no mmi auto-configure"
        },
        {
            "key": "origin",
            "origin": "no mmi pvc"
        },
        {
            "key": "origin",
            "origin": "mmi snmp-timeout 180"
        },
        {
            "key": "origin",
            "origin": "ip auth-proxy max-login-attempts 5"
        },
        {
            "key": "origin",
            "origin": "ip admission max-login-attempts 5"
        },
        {
            "key": "origin",
            "origin": "no ip domain lookup"
        },
        {
            "key": "origin",
            "origin": "ip cef"
        },
        {
            "key": "origin",
            "origin": "no ipv6 cef"
        },
        {
            "key": "origin",
            "origin": "multilink bundle-name authenticated"
        },
        {
            "key": "origin",
            "origin": "crypto pki token default removal timeout 0"
        },
        {
            "childs": [
                {
                    "key": "origin",
                    "origin": "host 158.4.255.37"
                },
                {
                    "key": "origin",
                    "origin": "host 158.4.255.38"
                }
            ],
            "key": "origin",
            "origin": "object-group network netgrp1"
        },
        {
            "childs": [
                {
                    "key": "origin",
                    "origin": "icmp"
                },
                {
                    "key": "origin",
                    "origin": "ospf"
                }
            ],
            "key": "origin",
            "origin": "object-group service srvgrp1"
        },
        {
            "key": "origin",
            "origin": "username nb password 0 nb"
        },
        {
            "key": "origin",
            "origin": "redundancy"
        },
        {
            "childs": [
                {
                    "key": "origin",
                    "origin": "network 158.4.0.168 0.0.0.3"
                },
                {
                    "key": "origin",
                    "origin": "network 158.4.0.172 0.0.0.3"
                }
            ],
            "key": "origin",
            "origin": "router eigrp 1"
        },
        {
            "childs": [
                {
                    "key": "origin",
                    "origin": "router-id 1.1.1.8"
                },
                {
                    "key": "origin",
                    "origin": "network 192.168.240.8 0.0.0.7 area 2"
                }
            ],
            "key": "origin",
            "origin": "router ospf 1024"
        },
        {
            "key": "origin",
            "origin": "ip forward-protocol nd"
        },
        {
            "key": "origin",
            "origin": "no ip http server"
        },
        {
            "key": "origin",
            "origin": "no ip http secure-server"
        },
        {
            "childs": [
                {
                    "key": "origin",
                    "origin": "deny   158.4.233.29"
                },
                {
                    "key": "origin",
                    "origin": "permit any"
                }
            ],
            "key": "origin",
            "origin": "ip access-list standard R1toR3"
        },
        {
            "childs": [
                {
                    "key": "origin",
                    "origin": "deny   ip 158.4.255.32 0.0.0.7 any"
                },
                {
                    "key": "origin",
                    "origin": "permit ip any any"
                }
            ],
            "key": "origin",
            "origin": "ip access-list extended R3toR1"
        },
        {
            "key": "origin",
            "origin": "access-list 1 permit 158.4.255.37 log"
        },
        {
            "key": "origin",
            "origin": "access-list 1 deny   158.4.255.36"
        },
        {
            "key": "origin",
            "origin": "access-list 1 deny   158.4.255.38 log"
        },
        {
            "childs": [
                {
                    "key": "origin",
                    "origin": "logging synchronous"
                }
            ],
            "key": "origin",
            "origin": "line con 0"
        },
        {
            "key": "origin",
            "origin": "line aux 0"
        },
        {
            "childs": [
                {
                    "key": "origin",
                    "origin": "login local"
                },
                {
                    "key": "origin",
                    "origin": "transport input all"
                }
            ],
            "key": "origin",
            "origin": "line vty 0 4"
        },
        {
            "childs": [
                {
                    "key": "origin",
                    "origin": "periodic weekdays 19:15 to 19:16"
                }
            ],
            "key": "origin",
            "origin": "time-range ww"
        },
        {
            "key": "origin",
            "origin": "end"
        }
    ],
    "hostname": "example",
    "interfaces": [
        {
            "interface": "Loopback0",
            "ip address": "158.4.255.44 255.255.255.255"
        },
        {
            "interface": "Ethernet0/0",
            "ip address": "158.4.0.170 255.255.255.252"
        },
        {
            "interface": "Ethernet0/1",
            "ip address": "158.4.0.173 255.255.255.252"
        },
        {
            "interface": "Ethernet0/2",
            "ip address": null,
            "shutdown": "true"
        },
        {
            "interface": "Ethernet0/3",
            "ip address": "192.168.240.11 255.255.255.248"
        },
        {
            "encapsulation": "ppp",
            "interface": "Serial1/0",
            "serial restart-delay": "0"
        },
        {
            "interface": "Serial1/1",
            "ip address": "158.4.255.66 255.255.255.252",
            "serial restart-delay": "0"
        },
        {
            "interface": "Serial1/2",
            "ip address": null,
            "serial restart-delay": "0",
            "shutdown": "true"
        },
        {
            "interface": "Serial1/3",
            "ip address": null,
            "serial restart-delay": "0",
            "shutdown": "true"
        }
    ],
    "version": "15.2"
}

)";


TEST(ParseConfigToJsonTest, OneRealConfigurefile)
{
	ParsedConfigResultShouldEqualJson(strConfigContext, strJsonString);
}