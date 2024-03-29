# -*- coding: utf-8 -*-
import os
import requests
from lxml import html
    
headers = {
      'Host': 'm.newsmth.net',
      'Accept-Language': 'zh-CN,zh;q=0.8,en;q=0.6',
      'Connection': 'keep-alive',
      'Pragma': 'no-cache',
      'Cache-Control': 'no-cache',
      'Upgrade-Insecure-Requests': '1',
      'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
      'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_4) '
                    'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/57.0.2987.133 Safari/537.36',
      'Cookie': '你的cookei'
}
    
    
def save(text, filename='temp', path='outbox'):
      fpath = os.path.join(path, filename)
      with open(fpath, 'wb') as f:
          print('output:', fpath)
          f.write(text)
    
def save_letter(letter_url):
      resp = requests.get('https://m.newsmth.net'+letter_url,headers=headers)
      page = resp.content
      print(page)
      save(page,letter_url.replace('/mail/outbox/','outbox')+'.html')
    
def crawl(url, outbox):
      resp = requests.get(url, headers=headers)
      page = resp.content
      root = html.fromstring(page)
      letters = root.xpath('//li/a//\@href')
      # print(page.decode())
      for letter in letters :
          if letter not in outbox and (letter.find('mail') > 0):
                outbox.append(letter)
    
    
if __name__ == '__main__':
      # 注意在运行之前，先确保该文件的同路径下存在一个download的文件夹, 用于存放爬虫下载的邮件
      obox = [] # empty list
      p=1
      while(p<96): #如果用4p只得到40结果，用96p得到64个。
        url = 'https://m.newsmth.net/mail/outbox?p='+ str(p)    
        crawl(url, obox)
        p=p+1
      #print(obox)
      for letter in obox :
            save_letter(letter)
