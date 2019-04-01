#!/usr/bin/env python
# -*- coding: utf-8 -*-
 
import requests
import json
import os

geturl = 'http://18.222.252.3/'
posturl = 'http://18.222.252.3/time_management/add-item'
headers={
    'Accept': 'application/json, text/javascript, */*; q=0.01',
    'Accept-Encoding': 'gzip, deflate',
    'Accept-Language': 'zh-CN,zh;q=0.9',
    'Connection': 'keep-alive',
    'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8',    #!!!提交表单格式!!!
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.108 Safari/537.36'
}

#运行cmd,生成data.txt
cpptest="LogLib.exe"
print("python execute cpp program:")
os.system(cpptest)

#获取数据

#数据itemlist: [ {ClassName: <type>string, WindowText: <type>string, ProcessName: <type>string, topWindow: <type>int} ]
# topWindow 1:是   0:不是
#返回值: "item=" + json.dumps(itemlist) + "&" + "csrfmiddlewaretoken=xxxxxxx"
f = open("data.txt", "r", encoding = "ANSI")
linesdata = f.readlines()
lineslength = len(linesdata)
loc = 0

itemlist = []
if(lineslength%4 == 0):
    while(loc < lineslength):
        sondict = {}
        sondict.update({"ClassName" : linesdata[loc].rstrip("ClassName:")[:-1]})
        loc = loc + 1
        sondict.update({"WindowText" : linesdata[loc].rstrip("WindowText:")[:-1]})
        loc = loc + 1
        sondict.update({"ProcessName" : linesdata[loc].rstrip("ProcessName:")[:-1]})
        loc = loc + 1
        if(linesdata[loc][:-1] == "topWindow"):
            sondict.update({"topWindow" : 1})
        else:
            sondict.update({"topWindow" : 0})
        loc = loc + 1
        itemlist.append(sondict)
itemjsondata = json.dumps(itemlist)
f.close()

#删除data.txt
os.remove("data.txt")

#GET
response = requests.get(geturl)
cookie_value = ''
cookie_key = ''
for key,value in response.cookies.items():     #response.cookies其实只有一个,就先这么写吧
    cookie_value = value
    cookie_key = key
cookies = {cookie_key : cookie_value}          #设置cookies
# 返回信息
#print(response.text)
# 返回响应头
print("GET response code:", response.status_code)


#POST
postdata = [('item', itemjsondata),
            ('csrfmiddlewaretoken', cookie_value),
             ]   #标准表单格式

response = requests.post(posturl, data = postdata, cookies = cookies, headers = headers)
# 返回信息
#print(response.text)
# 返回响应头
print("POST response code:", response.status_code)
