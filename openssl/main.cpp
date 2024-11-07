#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>
#include <string>
 
int main() {
    EVP_ENCODE_CTX *ctx;
    int len, outlen, rc;
    unsigned char buffer[1024];
    unsigned char key[EVP_MAX_KEY_LENGTH];
    unsigned char iv[EVP_MAX_IV_LENGTH];
    unsigned char *out;
 
    // 初始化变量
    ctx = EVP_ENCODE_CTX_new();
    out = (unsigned char*)malloc(1024); // 假设输入的解密文本不会超过1024字节
 
    // 初始化key和iv，这里需要根据实际情况进行设置
    memset(key, 0x00, EVP_MAX_KEY_LENGTH);
    memset(iv, 0x00, EVP_MAX_IV_LENGTH);
 
    // 初始化解密上下文
    //EVP_DecryptInit(ctx, EVP_aes_256_cbc(), key, iv);
    EVP_EncodeInit(ctx);
 
    // 假设enc_in是要解密的数据，enc_len是其长度
    std::string enc_data = "hello world!";
    unsigned char *enc_in = (unsigned char*)enc_data.data();
    int enc_len = enc_data.size();
 
    // 设置解密更新的输出buffer
    EVP_CIPHER_CTX_set_padding(ctx, 0); // 如果需要，关闭填充
 
    // 解密数据
    EVP_DecryptUpdate(ctx, out, &outlen, enc_in, enc_len);
 
    // 解密结束
    EVP_DecryptFinal_ex(ctx, out + outlen, &len);
 
    // 释放资源
    EVP_CIPHER_CTX_free(ctx);
 
    // 输出解密后的数据
    printf("Decrypted data: %s\n", out);
 
    free(out);
    return 0;
}