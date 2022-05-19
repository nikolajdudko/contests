#!/usr/bin/env python3

import vk_api
import random as r
from pprint import pprint
import time
from selenium import*
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from io import StringIO
import base64
import sys
from vk_api.longpoll import VkLongPoll, VkEventType
from vk_api.keyboard import VkKeyboard, VkKeyboardColor
import datetime
import colorama as co
from prettytable import PrettyTable
import requests as re
from bs4 import BeautifulSoup
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities
import math


def probability(k, LIST, SUBJECT, MARK=4, N=5):
    if LIST[SUBJECT] == []:
        return 'нет оценок'
    #Íàéäåì âåðîÿòíîñòü ïîëó÷åíèÿ êàæäîé îòöåíêè

    P = [0, 0, 0, 0]
    for q in range(2, 6):
        y = 1
        l1, l2, l3, l4 = [], [], [], []
        Ei, Di = 0, 0

        for i in range(1, len(LIST[SUBJECT])):
            if LIST[SUBJECT][i] == q:
                Ei = (Ei * (i - 1) + 1) / i
            else:
                Ei = Ei * (i - 1) / i
            Di = i
            l1.append(Ei * math.atan(Di))
            l2.append(math.atan(Di) ** 2)
            l3.append(Di * Ei / (Di ** 2 + 1))
            l4.append(Di * math.atan(Di) / (Di ** 2 + 1))

        MIN = sum(l3) / sum(l4) - sum(l1) / sum(l2)
        f_y = MIN

    #Ïîäáèðàåì ïðèìåðíûé êîðåíü
        while f_y <= MIN:
            y += 1
            if y > math.tan(3.14 / 2 / N) / N:
                break
            MIN = f_y
            l1, l2, l3, l4 = [], [], [], []
            for i in range(1, len(LIST[SUBJECT])):
                if LIST[SUBJECT][i] == q:
                    Ei = (Ei * (i - 1) + 1) / i
                else:
                    Ei = Ei * (i - 1) / i
                Di = i
                l1.append(Ei * math.atan(Di * y))
                l2.append(math.atan(Di * y) ** 2)
                l3.append(Di * Ei / (Di ** 2 * y ** 2 + 1))
                l4.append(Di * math.atan(Di * y) / (Di ** 2 * y ** 2 + 1))
            f_y = sum(l3) / sum(l4) - sum(l1) / sum(l2)

        #Àïðîêñèìàöèÿ äëÿ íàáîðîâ òî÷åê, íå àïðîêñèìèðóþùèõñÿ arctg

        if y > math.tan(3.14 / 2 / N) / N:
            P[q - 2] = 0
            for i in range(1, len(LIST[SUBJECT])):
                if LIST[SUBJECT][i] == q:
                    Ei = (Ei * (i - 1) + 1) / i
                else:
                    Ei = Ei * (i - 1) / i
                P[q - 2] = (P[q - 2] * (i - 1) + Ei) / i

        y = y - 1

    #Àëãîðèòì Íüþòîíà

        L1, L2, L3, L4, L5, L6, L7, L8, L9, L10, L11 = [], [], [], [], [], [], [], [], [], [], []
        y1, y2 = abs(y) + 0.0001 + 0.001, y + 0.0001
        Ei, Di = 0, 0

        while abs(y1 - y2) >= 0.001:
            y1 = y2
            l1, l2, l3, l4 = [], [], [], []
            L1, L2, L3, L4, L5, L6, L7, L8, L9, L10, L11 = [], [], [], [], [], [], [], [], [], [], []
            for i in range(1, len(LIST[SUBJECT])):
                if LIST[SUBJECT][i] == q:
                    Ei = (Ei * (i - 1) + 1) / i
                else:
                    Ei = Ei * (i - 1) / i
                Di = i
                l1.append(Ei * math.atan(Di * y1))
                l2.append(math.atan(Di * y1) ** 2)
                l3.append(Di * Ei / (Di ** 2 * y1 ** 2 + 1))
                l4.append(Di * math.atan(Di * y1) / (Di ** 2 * y1 ** 2 + 1))
                L1.append(-2 * Ei * Di ** 3 * y1 / (Di ** 2 * y1 ** 2 + 1) ** 2)
                L2.append(Di * math.atan(Di * y1) / (Di ** 2 * y1 ** 2 + 1))
                L3.append(math.atan(Di * y1) ** 2)
                L4.append(-2 * Di * math.atan(Di * y1) / (Di ** 2 * y1 ** 2 + 1))
                L5.append(Ei * math.atan(Di * y1))
                L6.append(Ei * Di / (Di ** 2 * y1 ** 2 + 1))
                L7.append(math.atan(Di * y1) ** 2)
                L8.append(Di * math.atan(Di * y1) / (Di ** 2 * y1 ** 2 + 1))
                L9.append(Di * Ei / (Di ** 2 * y1 ** 2 + 1))
                L10.append(2 * Di ** 3 * y1 * math.atan(Di * y1) / (Di ** 2 * y1 ** 2 + 1) ** 2)
                L11.append(-1 * Di ** 2 / (Di ** 2 * y1 ** 2 + 1) ** 2)

            y2 = y1 - (sum(l3) / sum(l4) - sum(l1) / sum(l2)) / (sum(L1) / sum(L2) - 1 / (sum(L3)) ** 2 * sum(L4) * sum(L5) - sum(L6) / sum(L7) + 1 / (sum(L8)) ** 2 * sum(L9) * (sum(L10) + sum(L11)))

    #Íàéäåì ïàðàìåòðû À è Â äëÿ f(x) = A * arctg(B * x)

        B = y2

        for i in range(1, len(LIST[SUBJECT])):
            if LIST[SUBJECT][i] == q:
                Ei = (Ei * (i - 1) + 1) / i
            else:
                Ei = Ei * (i - 1) / i
            Di = i
            l1.append(Ei * math.atan(Di * B))
            l2.append(math.atan(Di * B) ** 2)

        A = sum(l1) / sum(l2)

    #Ïðåäåë f(x) = A * arctg(B * x) ðàâåí À * ï/2

        if P[q - 2] == 0:
            P[q - 2] = A * 3.14 / 2

    #Íàéäåì äèàïîçîí

    for i in k:
        if SUBJECT in i:
            avg = a(i)
    Sr = float(avg)
    if MARK == 5:
        lim1 = 5
        lim2 = 4.5
    else:
        lim1 = MARK + 0.5
        lim2 = MARK - 0.5

    LIM1 = math.floor(lim1 * (N + len(LIST[SUBJECT])) - Sr * len(LIST[SUBJECT]))
    LIM2 = math.ceil(lim2 * (N + len(LIST[SUBJECT])) - Sr * len(LIST[SUBJECT]))

    #LIM2 <= 5 * x5 + 4 * x4 + 3 * x3 + 2 * x2 <= LIM1, x5 + x4 + x3 + x2 = N

    ans = []
    for x2 in range(N // 2 + 1):
        for x3 in range(N // 3 + 1):
            for x4 in range(N // 4 + 1):
                for x5 in range(N // 5 + 1):
                    if LIM2 <= 5 * x5 + 4 * x4 + 3 * x3 + 2 * x2 <= LIM1:
                        ans.append(([x2, x3, x4, x5]))

    #P(mark)

    P_mark = 0
    for i in range(len(ans)):
        P_mark += P[0] ** ans[i][0] * P[1] ** ans[i][1] * P[2] ** ans[i][2] * P[3] ** ans[i][3]
    cyka = ''


    for i in range(len(P)):
        cyka += str(i + 2) + ' - ' + str(P[i]) + ' \n'
    return cyka


def infa_table():
    BASE_URL = 'https://server.179.ru/ejudge/stand/mp/stand.php?contest=908'

    r = re.get(BASE_URL)
    soap = BeautifulSoup(r.text, "html.parser")
    b = [i.get_text()[:-4] for i in soap.find_all('td', class_='name')]
    a = [i.get('title').split('-')[0].strip() for i in soap.find_all('td', class_='verdict OK')]
    c = [i.get('title').split('-')[0].strip() for i in soap.find_all('td', class_='verdict PR')]
    table = PrettyTable(["человек", "  сдал  ", 'ожидает подтвеждения'])
    for i in b:
        table.add_row(
            [i, str(a.count(i)), str(c.count(i))])
        table.add_row(['', '', ''])
    return table


def f(login, pos):
    try:

        driver = webdriver.Safari()


        url = 'https://www.mos.ru/pgu/ru/application/dogm/journal/'
        driver.get(url)
        driver.find_element_by_id("loginDv").send_keys(login)
        driver.find_element_by_id("password").send_keys(pos)
        driver.find_element_by_class_name('btn').click()

        time.sleep(5)
        driver.get('https://dnevnik.mos.ru/progress/all_marks')
        time.sleep(10)
        result = []

        divs = driver.find_elements_by_xpath('//div[@class="all-marks-data"]')
        for div in divs:
            name = div.find_element_by_xpath('./div').text
            marks = ', '.join([el.text.replace('\t', '').replace('\n', '') for el in div.find_elements_by_xpath('.//span[@class="mark-value"]')])
            for i in ['22', '23', '24', '25', '32', '33', '34', '35', '42', '43', '44', '45', '52', '53', '54', '55']:
                marks = marks.replace(i, (i[0] + ' ') * int(i[1]))

            result.append(name + '-' + marks)
        driver.close()
        if result == []:
            result = ['не зашел, поробуй еще раз']
    except BaseException as E:
        print(E)
        driver.close()
        return ['не зашел, поробуй еще раз']
    return result

def get(vk_session, id_group):
    try:
        max_num = vk_session.photos.getAll(owner_id=id_group, count=0)['count']
        if max_num == 0:
            return get(vk_session, str((int(id_group) - 1)))
        num = r.randint(1, max_num)
        pictures = vk_session.photos.getAll(owner_id=id_group, count=4, offset=num)['items']
        buf = []
        for element in pictures:
            buf.append('photo' + id_group + '_' + str(element['id']))
        at = ','.join(buf)
        if at == '':
            at = get(vk_session, str((int(id_group) - 1)))
        return at
    except Exception as E:
        print('1)', E)
        if E == ' [15] Access denied: no access to group':
            return get(vk_session, str((int(id_group) - 1)))
        return 'ошибка'

def create_keyboard(response):
    keyboard = VkKeyboard(one_time=False)
    if '/эдж' in response.lower() or ('/eще статистики' in response.lower() and id in marks_global):
        keyboard = VkKeyboard(one_time=True)
        keyboard.add_button('/_1', color=VkKeyboardColor.POSITIVE, payload='')
        keyboard.add_button('/_2', color=VkKeyboardColor.POSITIVE, payload='')
        keyboard.add_line()
        keyboard.add_button('/_3', color=VkKeyboardColor.POSITIVE, payload='')
        keyboard.add_button('/_4', color=VkKeyboardColor.POSITIVE, payload='')
        keyboard.add_line()
        keyboard.add_button('/_5', color=VkKeyboardColor.POSITIVE, payload='')
        keyboard.add_line()
        keyboard.add_button('закрыть', color=VkKeyboardColor.NEGATIVE, payload='')
    elif response.lower() in ['/_2', '/_3', '/_4', '/_5']:
        keyboard = VkKeyboard(one_time=True)
        lessons = [j.split('-')[0] for j in marks_global.get(id, ['введите логин и пароль'])]
        for les in range(len(lessons)):
            if les % 4 == 0 and les != 0:
                keyboard.add_line()
            if len(lessons[les]) >= 37:
                st = lessons[les][:-3] + response[-1]
            else:
                st = lessons[les] + response[-1]
            keyboard.add_button(st, color=VkKeyboardColor.POSITIVE, payload='')
    elif response.lower() in ['закрыть', 'пока']:
        if id in marks_global:
            del marks_global[id]
        sent(peer_id=id, message="до скорого", keyboard=None)
        return keyboard.get_empty_keyboard()
    elif response:
        keyboard.add_button('закрыть', color=VkKeyboardColor.DEFAULT, payload='')
        keyboard.add_button('/котики', color=VkKeyboardColor.POSITIVE, payload='')
        keyboard.add_line()
        keyboard.add_button('красная кнопка', color=VkKeyboardColor.NEGATIVE, payload='')
        keyboard.add_button('/инструкция', color=VkKeyboardColor.PRIMARY, payload='')
        keyboard.add_line()
        keyboard.add_button('/eще статистики', color=VkKeyboardColor.POSITIVE, payload='')

    keyboard = keyboard.get_keyboard()
    return keyboard

def sent(peer_id=id, message=None, keyboard=None, attachment=None):
    rand = str(r.randint(10 ** 8, 10 ** 9 - 1))
    vk.messages.send(peer_id=peer_id, random_id=rand, message=message, keyboard=keyboard, attachment=attachment)
    return

def a(i):
    s = 0
    c = 0
    print(i.split('-')[1])
    for j in i.split('-')[1]:
        if j.isdigit():
            s += int(j)
            c += 1
    if c != 0:
        return str(round(s/c, 7))
    else:
        return 'нет оценок'

def graph(List):
    ans = ''
    for i in range(5, 1, -1):
        ans += str(i) + '|'
        for j in range(len(List)):
            if List[j] == i:
                ans += '.'
            else:
                ans += ' '
        ans += '\n'
    ans += '1|' + '_' * (len(List) + 1)
    return ans




k = vk_api.VkApi(login='', password='')

try:
    k.auth()
except vk_api.AuthError as error_msg:
    print(error_msg)

vk_session = k.get_api()


vk = vk_api.VkApi(token='')

vk._auth_token()
vk = vk.get_api()
instraction = '''Для получения оценок необходимо написать сообщение в формате '/эдж логин пароль'. '''
instraction2 = '''Выберите функции: \n\n 1) Все оценки \n\n 2) Оценки по предмету \n\n 3) средний бал 
 \n 4) График успеваемости  \n
5)  Вероятность оценки \n\n
   Выберете нужный пункт на клавиатуре.
   Для повторнолго получения статистики логин и пароль вводить не надо, для обновления оценок просто закройте клавиатуру. '''
marks_global = dict()
vvod = 'введите логин и пароль'

while True:
    try:
        messages = vk.messages.getConversations(offset=0, count=20, filter='unanswered')
        if messages["count"] >= 1 and messages['items'][0]['conversation']['unanswered']:
            id = messages["items"][0]["last_message"]["from_id"]
            body = messages["items"][0]["last_message"]["text"]
            if body:
                keyboard = create_keyboard(body)
            print(time.strftime("%H:%M:%S", time.localtime(messages['items'][0]['last_message']['date'])) + ' - ' + body)
            if '/эдж' in body.lower():
                body = body.split()
                if len(body) < 3:
                    sent(peer_id=id, message='неверный формат', keyboard=keyboard)
                login = body[1]
                pos = body[2]
                k = f(login, pos)
                if k != ['не зашел, поробуй еще раз']:
                    marks_global[id] = k
                    sent(peer_id=id, message=instraction2, keyboard=keyboard)
                else:
                    sent(peer_id=id, message=k[0], keyboard=None)
            elif body.lower() == '/котики':
                try:
                    a = get(vk_session, '-23300841')
                    sent(peer_id=id, attachment=a, keyboard=keyboard)
                except Exception as E:
                    print(E)
                    sent(peer_id=id, message='Error 404' + E, keyboard=keyboard)
            elif 'как дела' in body.lower():
                sent(peer_id=id, message="нормас", keyboard=keyboard)
            elif body.lower() == '/просто кнопка':
                try:
                    k = str(r.randint(-9999999, -100000))
                    a = get(vk_session, k)
                    print(a)
                    if a != 'ошибка':
                        # sent(peer_id='431885695', attachment=a, keyboard=keyboard)
                        sent(peer_id=id, attachment=a, keyboard=keyboard)
                except Exception as E:
                    print(E)
                    sent(peer_id=id, message='Error 404' + E, keyboard=keyboard)
            elif body.lower() == 'красная кнопка':
                sent(peer_id=id, attachment='photo-128883021_432149346')
            elif body.lower() == '/инструкция':
                sent(peer_id=id, message=''' ''', keyboard=keyboard)
            elif body.lower() == '/информатика':
                sent(peer_id=id, message=infa_table(), keyboard=keyboard)
            elif body.lower() == '/eще статистики':
                if id in marks_global:
                    sent(peer_id=id, message=instraction2, keyboard=keyboard)
                else:
                    sent(peer_id=id, message=vvod, keyboard=None)
            elif body.lower() == '/_1':
                k = marks_global.get(id, [vvod])
                for i in k:

                    sent(peer_id=id, message=i, keyboard=keyboard)
            elif body.lower() in ['/_2', '/_3', '/_4', '/_5']:
                sent(peer_id=id, message='выбери предмет', keyboard=keyboard)
            elif body[:-1] in ''.join([j.split('-')[0] for j in marks_global.get(id, ['***'])]) and body[-1] == '2':
                body = body[:-1]
                k = marks_global.get(id, [vvod])
                for i in k:
                    if body in i:
                        sent(peer_id=id, message=i, keyboard=keyboard)
            elif body[:-1] in ''.join([j.split('-')[0] for j in marks_global.get(id, ['***'])]) and body[-1] == '3':
                body = body[:-1]
                k = marks_global.get(id, [vvod])
                print(k)
                if k == [vvod]:
                    sent(peer_id=id, message=k[0], keyboard=keyboard)
                else:
                    for i in k:
                        if body in i:
                            sent(peer_id=id, message=a(i), keyboard=keyboard)
            elif body[:-1] in ''.join([j.split('-')[0] for j in marks_global.get(id, ['***'])]) and body[-1] == '5':
                body = body[:-1]
                k = marks_global.get(id, [vvod])
                k_forst = dict()
                mrk = []
                if k == [vvod]:
                    sent(peer_id=id, message=k[0], keyboard=keboard)
                else:
                    for i in range(len(k)):
                        xxx = k[i].split('-')
                        if body in xxx[0]:
                            body = xxx[0]
                        for q in xxx[1]:
                            if q.isdigit():
                                mrk.append(int(q))
                        k_forst[xxx[0]] = mrk
                        mrk = []
                    sent(peer_id=id, message=probability(k, k_forst, body), keyboard=keyboard)
            elif body[:-1] in ''.join([j.split('-')[0] for j in marks_global.get(id, ['***'])]) and body[-1] == '4':
                body = body[:-1]
                k = marks_global.get(id, [vvod])
                mrk = []
                if k == [vvod]:
                    sent(peer_id=id, message=k[0], keyboard=keyboard)
                else:
                    for i in k:
                        if body in i:
                            f = i.split('-')[1]
                            for p in f:
                                if p.isdigit():
                                    mrk.append(int(p))
                    sent(peer_id=id, message=graph(mrk), keyboard=keyboard)

            elif body.lower() == '666':
                sent(peer_id=id, message='oke')
                pass
                # sys.exit()
            else:
                sent(peer_id=id, message="hello", keyboard=keyboard)
    except Exception as E:
        # sent(peer_id=id, message="ошибка", keyboard=keyboard)
        time.sleep(1)
        print('ошибка', E)

