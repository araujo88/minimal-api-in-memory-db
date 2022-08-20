import requests

BASE_URL = "http://localhost:8001/"

data = {"name": "Giga", "surname": "Chad"}

r = requests.get(url=f"{BASE_URL}users")
print(r.json())

r = requests.get(url=f"{BASE_URL}users/0")
print(r.json())

r = requests.get(url=f"{BASE_URL}users/1")
print(r.json())

r = requests.get(url=f"{BASE_URL}users/234234")
print(r.json())

r = requests.delete(url=f"{BASE_URL}users/0")
print(r.json())

r = requests.get(url=f"{BASE_URL}users")
print(r.json())

r = requests.post(url=f"{BASE_URL}users", data=data)
print(r.json())
