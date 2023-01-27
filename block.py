import random
# inp = input('Enter two character')
key = 1720050378
key_bit = [0]*32
# x = chr(n)
# print(ord(x))

def convert_string_int(w):
    a = ord(w[0])
    b = ord(w[1])

    a <<= 8
    a += b

    str_ = [0]*16

    for i in range(0,16):
        if a&(1<<i):
            str_[i] = 1
        else:
            str_[i] = 0
    print("str_")
    print(str_)
    return str_




def convert_int_string(w_ans):
    a = 0
    ans = ''
    for i in range(0,8):
        if w_ans[i] == 1:
            a += (1<<i)
    
    ans += chr(a)

    a= 0 

    for i in range(8,16):
        if w_ans[i] == 1:
            a += (1<<(i-8))
    ans += chr(a)

    ans = ans[::-1]
    return ans


def key_mixing(subkey,w_num):
    xor_ = [0]*16

    for i in range(0,16):
        xor_[i] = subkey[i] ^ w_num[i]
    
    sbox = [[0 for i in range(4)] for j in range(4)]

    for i in range(0,4):
        for j in range(0,4):
            sbox[i][j] = xor_[4*i + j]
    
    print("sbox")
    print(sbox)
    return sbox



def key_permutation(sbox):
    permute = list()
    for i in range(0,4):
        for j in range(0,4):
            permute.append(sbox[j][i])
    
    return permute




def func(round,w_num):
    print('round')
    print(round)
    print('w_num')
    print(w_num)
    if round == 1:
        subkey = list()
        for i in range(0,16):
            subkey.append(key_bit[i])
        
        print('subkey')
        print(subkey)
        sbox = key_mixing(subkey,w_num)
        permut = key_permutation(sbox)
        print('permut')
        print(permut)
        return permut
    
    elif round == 2:
        subkey = list()
        for i in range(4,20):
            subkey.append(key_bit[i])
        
        print('subkey')
        print(subkey)
        sbox = key_mixing(subkey,w_num)
        permut = key_permutation(sbox)
        print('permut')
        print(permut)
        return permut

    elif round == 3:
        subkey = list()
        for i in range(8,24):
            subkey.append(key_bit[i])
        
        print('subkey')
        print(subkey)
        sbox = key_mixing(subkey,w_num)
        permut = key_permutation(sbox)
        print('permut')
        print(permut)
        return permut

    elif round == 4:
        subkey = list()
        for i in range(12,28):
            subkey.append(key_bit[i])
        
        print('subkey')
        print(subkey)
        sbox = key_mixing(subkey,w_num)
        permut = list()

        for i in range(0,4):
            for j in range(0,4):
                permut.append(sbox[i][j])
        
        print('permut')
        print(permut)
        return permut

    
    elif round == 5:
        subkey = list()
        for i in range(16,32):
            subkey.append(key_bit[i])
        
        print('subkey')
        print(subkey)
        permut = list()
        
        for i in range(0,16):
            permut.append(subkey[i] ^ w_num[i])
        print('permut')
        print(permut)
        return permut



if __name__ == "__main__":
    w = "aa"

    print('key')
    print(key)
    
    for i in range(0,32):
        if (key&(1<<i)):
            # print('here')
            key_bit[i] = 1
        
    print("key_bit")
    print(key_bit)
    w_num = convert_string_int(w)

    for i in range(1,6):
        w_num = func(i,w_num)
    

    # print('round 5')

    # subkey = list()
    # for i in range(16,32):
    #     subkey.append(key_bit[i])
    
    # finalbox = key_mixing(subkey,w_num)

    # print('finalbox')
    # print(finalbox)
    # w_ans = list()

    # for i in range(0,4):
    #     for j in range(0,4):
    #         w_ans.append(finalbox[i][j])

    # print('w_ans')
    # print(w_ans)
    # ret = convert_int_string(w_ans)
    ret = convert_int_string(w_num)

    check = convert_string_int(ret)
    print('check')
    print(check)

    print(ret)