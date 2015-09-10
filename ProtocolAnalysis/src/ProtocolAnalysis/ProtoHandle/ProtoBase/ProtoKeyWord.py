#-*- encoding=utf-8 -*-


# Proto 的关键字
class ProtoKeyWord(object):
    ePackage = "package"
    eMessage = "message"
    eEnum = "enum"
    eHeader = "header"
    eImport = "import"
    ePragma = "pragma"
    
    eSingleLineComment = "//"
    eMulLineCommentStart = "/**"
    eMulLineCommentEnd = "*/"
    
    #eOptional = "optional"
    #eRepeated = "repeated"
    
    eLeftBrace = "{"
    eRightBrace = "}"
    eSemicolon = ";"
    eRightBraceSemicolon = "};"
    eBase = "base"      # 说明是基类中的成员
    
    
    #eInt8 = "int8" # 这个就是 char 类型，这种类型基本只能是数组 char pChar[32]
    eInt8 = "char"      # 注意如果是数组的话，m_typeName 永远是 char  uint8 这些，但是 m_propType 会记录成  eInt8Array ，注意这个小区别
    eUint8 = "uint8"
    
    eInt16 = "int16"
    eUint16 = "uint16"    
    
    eInt32 = "int32"
    eUint32 = "uint32"
    
    # 关键字分隔符
    sKeyWordDelimiter = ["package", "message", "enum", "header", "import"]
    

