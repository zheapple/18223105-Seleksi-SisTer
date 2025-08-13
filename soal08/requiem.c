#include <stdio.h>

#define MAXD 1000

// ===== Helper bitwise add & sub =====
unsigned char u8_add(unsigned char a, unsigned char b) {
    unsigned char carry;
ADD_LOOP:
    if (b == 0) return a;
    carry = a & b;
    a = a ^ b;
    b = carry << 1;
    goto ADD_LOOP;
}

unsigned char u8_sub(unsigned char a, unsigned char b) {
    unsigned char borrow;
SUB_LOOP:
    if (b == 0) return a;
    borrow = (~a) & b;
    a = a ^ b;
    b = borrow << 1;
    goto SUB_LOOP;
}

unsigned char inc(unsigned char x) { return u8_add(x, 1); }
unsigned char dec(unsigned char x) { return u8_sub(x, 1); }

// ===== Precompute tabel digit × digit =====
static const unsigned char mul10[10][10] = {
    {0,0,0,0,0,0,0,0,0,0},
    {0,1,2,3,4,5,6,7,8,9},
    {0,2,4,6,8,10,12,14,16,18},
    {0,3,6,9,12,15,18,21,24,27},
    {0,4,8,12,16,20,24,28,32,36},
    {0,5,10,15,20,25,30,35,40,45},
    {0,6,12,18,24,30,36,42,48,54},
    {0,7,14,21,28,35,42,49,56,63},
    {0,8,16,24,32,40,48,56,64,72},
    {0,9,18,27,36,45,54,63,72,81}
};

// ===== Precompute split 0..99 ke lo, hi (manual) =====
static const unsigned char split_lo[100] = {
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9
};

static const unsigned char split_hi[100] = {
    0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,1,1,1,
    2,2,2,2,2,2,2,2,2,2,
    3,3,3,3,3,3,3,3,3,3,
    4,4,4,4,4,4,4,4,4,4,
    5,5,5,5,5,5,5,5,5,5,
    6,6,6,6,6,6,6,6,6,6,
    7,7,7,7,7,7,7,7,7,7,
    8,8,8,8,8,8,8,8,8,8,
    9,9,9,9,9,9,9,9,9,9
};

// ===== Global arrays =====
char sa[MAXD+1], sb[MAXD+1];
unsigned char A[MAXD], B[MAXD], R[2*MAXD];

int main() {
    unsigned char la=0, lb=0;
    unsigned char i, j, k;
    unsigned char carry, prod, t, d, c;

    // baca string
    printf("Masukkan angka pertama: ");
    scanf("%s", sa);

    printf("Masukkan angka kedua: ");
    scanf("%s", sb);

    // hitung panjang sa
    i = 0;
LEN_A:
    if (sa[i] == 0) goto END_LEN_A;
    i = inc(i);
    goto LEN_A;
END_LEN_A:
    la = i;

    // hitung panjang sb
    i = 0;
LEN_B:
    if (sb[i] == 0) goto END_LEN_B;
    i = inc(i);
    goto LEN_B;
END_LEN_B:
    lb = i;

    // konversi ke LSB-first
    j = 0;
    i = dec(la);
FILL_A:
    A[j] = sa[i] & 0x0F;
    if (i == 0) goto END_FILL_A;
    i = dec(i);
    j = inc(j);
    goto FILL_A;
END_FILL_A:

    j = 0;
    i = dec(lb);
FILL_B:
    B[j] = sb[i] & 0x0F;
    if (i == 0) goto END_FILL_B;
    i = dec(i);
    j = inc(j);
    goto FILL_B;
END_FILL_B:

    // perkalian O(N²)
    i = 0;
LOOP_I:
    if (i == la) goto END_I;
    carry = 0;
    j = 0;
LOOP_J:
    if (j == lb) goto END_J;
    prod = mul10[ A[i] ][ B[j] ];
    t = u8_add(R[i+j], prod);
    t = u8_add(t, carry);
    d = split_lo[t];
    c = split_hi[t];
    R[i+j] = d;
    carry = c;
    j = inc(j);
    goto LOOP_J;
END_J:
    R[i+lb] = u8_add(R[i+lb], carry);
    i = inc(i);
    goto LOOP_I;
END_I:

    // cari indeks digit paling signifikan
    k = u8_add(la, lb);
    if (k == 0) k = 1;
    k = dec(k);
FIND_TOP:
    if (k == 0) goto END_FIND;
    if (R[k] != 0) goto END_FIND;
    k = dec(k);
    goto FIND_TOP;
END_FIND:

    // cetak dari MSB ke LSB
PRINT_LOOP:
    printf("%u", R[k]);
    if (k == 0) goto END_PRINT;
    k = dec(k);
    goto PRINT_LOOP;
END_PRINT:

    printf("\n");
    return 0;
}
