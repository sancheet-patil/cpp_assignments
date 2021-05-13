import base64

base64_String="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

def ConvertS2Bi():

    flag = 0
    i = 0
    stringofbase=""
    with open("Image.png" , "rb") as f:
            w = f.read()
        
    res =""
    for i in w:
        res = res + ( bin( i )[ 2 : ] ) . zfill( 8 )
    f.close()

    if (len(res)%6)==2:
        res = res + "0000"
        flag = 2
    if (len(res)%6)==4:
        res = res + "00"
        flag = 1
        
    i=0
    while(len(res[i:]) > 5):
        pos = int( res[ i : i + 6 ] , 2 )
        stringofbase = stringofbase + base64_String[ pos ]
        i = i + 6
        
    if (flag == 1):
        stringofbase = stringofbase + "="
    if (flag == 2):
        stringofbase = stringofbase + "=="

    stringofbase=stringofbase.encode()
    with open("PyBase_64Encoded.txt" , "wb") as d:
       d.write(stringofbase)
       
    d.close()

def ConvertS2Image():
    res=""
    stringofbase=b''
    padding =0

    with open("PyBase_64Encoded.txt" , "r") as d:
        w1 = d.read()
    d.close()
    for i in w1:
        if(i=='='):
            padding= padding + 1
        else:
            res= res + bin( base64_String.find( i ) )[ 2 : ] . zfill( 6 )
    
    
    if(padding == 1):
        res = res [ : -2 ]
    if(padding == 2):
        res = res [ : -4 ]

    reslen = len(res)
    if( len( res ) % 8 == 0 ):
        i=0
        while(i<reslen):
            pos = int( res [ i : i + 8 ] , 2 )
            stringB = chr( pos )
            stringofbase = stringofbase + stringB.encode(' latin1 ')
            i = i + 8

    with open("PyDecoded_Image.png" , "wb") as d:
        d.write( stringofbase )
    d.close()

ConvertS2Bi()    
ConvertS2Image()

