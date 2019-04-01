#!/usr/bin/env python
# -*- coding: utf-8 -*-
 
import requests
import json
import os
import psutil
import datetime
import time
from AppKit import NSWorkspace

#url for test
'''
geturl = 'http://127.0.0.1:8000/'
posturl = 'http://127.0.0.1:8000/time_management/add-item'
'''
geturl = 'http://18.222.252.3/'
posturl = 'http://18.222.252.3/time_management/add-item'


headers={
    'Accept': 'application/json, text/javascript, */*; q=0.01',
    'Accept-Encoding': 'gzip, deflate',
    'Connection': 'keep-alive',
    'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8',    #!!!
}


time.sleep(1)

#get the name and pid of the frontmost app
active_app_name = NSWorkspace.sharedWorkspace().frontmostApplication().localizedName()
active_pid = NSWorkspace.sharedWorkspace().frontmostApplication().processIdentifier()

print(active_app_name, active_pid)
print()


#use psutil to get more info
pidlist = psutil.pids()
if active_pid in pidlist:
    process = psutil.Process(active_pid)
    try:
        print("name:",process.name())
        print("pid:",active_pid)
        print("ppid:",process.ppid())
        print("gid:",process.gids())
        print("exe:",process.exe())
        p_time = datetime.datetime.fromtimestamp(process.create_time()).isoformat()
        print("creat_time:",p_time)
        print("dict:",process.as_dict(attrs=['pid', 'name', 'username']))
    except:
        print("error")



'''

f = open("data.txt", "r")
linesdata = f.read()
#lineslength = len(linesdata)

'''

print(datetime.datetime.now().isoformat())
test_data = {"process_name":process.name(),
                    "update_time":datetime.datetime.now().isoformat(),
                    "create_time":p_time,
                    "type":"data",
                    "username":"lmh from mac"}

#print(type(test_data))
json = json.dumps(test_data)

print(json)

#postdata = "item=" + linesdata
#f.close()

#print(postdata)

#删除data.txt
#os.remove("data.txt")

print()
#GET
response = requests.get(geturl)
print(response.text)
print(response.headers)
cookie_value = "mLEf68ArHFvgs8ewnY11sWBWpyXk2fpijbcS6XngiIrUgLzmFCRq8gwT63ypVxwu"
headers['Cookie'] = 'csrftoken=' + cookie_value



'''
for key,value in response.cookies.items():     #response.cookies其实只有一个
    cookie_value = value
    print("1")
headers['Cookie'] = key + '=' + cookie_value
# 返回信息
print(response.text)
# 返回响应头
print(response.status_code)
'''


#POST

postdata = [('item', json),
            ('csrfmiddlewaretoken', cookie_value),
             ]
#postdata = postdata + "&" + "csrfmiddlewaretoken=" + cookie_value

print(postdata)

response = requests.post(posturl, data = postdata, headers = headers)
# 返回信息
print(response.text)
# 返回响应头
print(response.status_code)
 
    



