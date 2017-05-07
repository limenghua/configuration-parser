cisco format configure file parse into json format
===

#项目主要有两个用意：
##1.尝试进行Config文件的解析，对原有的Config解析代码极不满意，不仅代码混乱，并且根本逻辑都是错误的
  尝试使用代码来描述自己的思路：
	（1）Config解析的数据输出结果采用json格式
	（2）解析采用以块为单位，依据代码自然的树状层次结构，且假定解析逻辑与父节点及兄弟节点无关。
	（3）解析分步完成，每次完成一小步的转换，要求转换需求简单，明确，清晰。
		 现主要由三步组成：1.将configure file解析为语句树，通过缩进来确定树之间的父子关系；2.分别对每一个子树的内容进行解析，生成解析后的json的树结构；3.调整解析后的json格式，根据需要合并父子节点。
		 
##2.尝试进行测试驱动开发，


#项目基本功能：Configure转json格式，example:
##configure file:

! Info via SNMP: sysoid=1.3.6.1.4.1.9.1.1,vendor=Cisco,model=ciscoGatewayServer,hostname=ACL_R2

version 15.2
!
hostname example
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

##解析后的json文件：
```javascript
{
 "hostname":"example",
 "interfaces":[
 {
 "interface":"Loopback0",
 "ip address":"158.4.255.44 255.255.255.255"
 },
 {
 "interface":"Ethernet0/0",
 "ip address":"158.4.0.170 255.255.255.252"
 },
 {
 "interface":"Ethernet0/1",
 "ip address":"158.4.0.173 255.255.255.252"
 },
 {
 "interface":"Ethernet0/2",
 "ip address":null,
 "shutdown":"true"
 },
 {
 "interface":"Ethernet0/3",
 "ip address":"192.168.240.11 255.255.255.248"
 },
 {
 "encapsulation":"ppp",
 "interface":"Serial1/0",
 "serial restart-delay":"0"
 },
 {
 "interface":"Serial1/1",
 "ip address":"158.4.255.66 255.255.255.252",
 "serial restart-delay":"0"
 },
 {
 "interface":"Serial1/2",
 "ip address":null,
 "serial restart-delay":"0",
 "shutdown":"true"
 },
 {
 "interface":"Serial1/3",
 "ip address":null,
 "serial restart-delay":"0",
 "shutdown":"true"
 }
 ],
 "version":"15.2"
}
```
