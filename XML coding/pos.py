
#!/usr/bin/env python3.3
import sys
import xml.etree.ElementTree as ET
from sys import argv
from collections import defaultdict

#keeps track of stalk in real-time
rtstock = defaultdict(int)

def pricecheck(itemid, items):
    for i in items:
        if(i.id == itemid):
            if(i.card=="y"):
                return float(i.price)
            else:
                return i.price
    return 0

def update_stock(itemid, items):
    for i in items:
        if(i.id == itemid):
            rtstock[i.name] = rtstock[i.name] - 1

def instock(itemid, items):
    for i in items:
        if(i.id == itemid):
            if(int(i.stock) == 0):
                return False
    return True

class Item(object):
    elts = ['name', 'price']
    def __init__(self, element):
        self.name = element.find('name').text
        self.id = element.get('id')
        self.stock = element.get('stock')
        self.card = element.get('card')
        for field in Item.elts:
            setattr(self, field, element.find(field).text)
        rtstock[self.name] = int(self.stock)
    def __str__(self):
        if(self.card == 'y'):
            return (self.name + self.id + self.stock + self.card)
        else:
            return (self.name + self.id + self.stock)

class Transac(object):
    attrs = ['itemID', 'timestamp', 'card']
    def __init__(self, element):
        for field in Transac.attrs:
            setattr(self, field, element.get(field))


doc_shop = ET.parse(argv[1])
shop = doc_shop.getroot()

doc_trans = ET.parse(argv[2])
trans = doc_trans.getroot()

items = list(map(Item,doc_shop.findall('.//item')))
transacs = list(map(Transac, doc_trans.findall('.//sale')))

total = 0

for t in transacs:
    for i in items:
        if(i.id == t.itemID):
            nm = i.name
            card_bool = i.card 
    if(card_bool == t.card == 'y'):
        total+=0.85 * float(pricecheck(t.itemID, items))
    else:
        total+=float(pricecheck(t.itemID, items))
    update_stock(t.itemID, items)
    if(not instock(t.itemID, items)):
        print("Warning: Inventory shows no stock for product", nm, "\nRecheck inventory.")
    for i in items:
        if(i.id == t.itemID):
            if(t.card == 'y' and not i.card == 'y'):
                print("Attempt to use discount card on non-discount product", nm)

for key in rtstock:
    if(rtstock[key]<1):
        print("Warning:", key, "stock depleted")
sys.stdout.write('\n$')
print(total)


