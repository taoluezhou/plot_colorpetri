#ifndef PETRI_H
#define PETRI_H



//定义存放Petri网信息的文档
#define FILE_NAME "matrix_of_petrinet.dat"

//定义库所最大扇入扇出单色弧个数
#define Max_inout_num 100

//定义库所变迁数量最大各100个
#define Max 100
//每个库所颜色个数的最大值
#define Max_color_num_ofplace 10
//变迁发生规则的最大个数
#define Max_rule_num  10
//每个变迁发生规则中条件个数的最大值
#define Max_color_num_inrule 10
//定义默认托肯容量
#define Default_Maxsize_token 15

#define Error 1
#define fuckrignt 0
#define OK 0
#define FError 2



struct arc{
    int id;//弧的编号
    int id_of_place;//与弧连接的库所编号
    int id_of_transition;//与弧连接的变迁编号
    /*方向：若值为1表示此弧的方向是从变迁到库所，即后关联矩阵描述的方向
            若值为0表示此弧的方向是从库所到变迁，即前关联矩阵描述的方向*/
    int direction;
    int id_of_rule;//该弧的颜色对应于变迁所有发生规则的编号
    int id_of_color;//该弧的颜色在库所所有颜色中的编号
    char color[100];//表示弧的颜色
    int maxsize;//表示此弧连接的库所中的托肯颜色与弧颜色一致的托肯的最大容量
    int init_val;//表示此弧连接的库所中的托肯颜色与弧颜色一致的托肯的初始值
    int num;   //消耗或产生颜色的数量
    //struct arc *next;
};

struct place{
    int id;//库所的编号
    int number_of_color;//库所的颜色个数
    //int place_token_num;//库所令牌种类数
    //QString token_name[20];//令牌名
    int size[Max_color_num_ofplace];//库所的容量（对于不同颜色的托肯有不同的容量）
    int init_number[Max_color_num_ofplace];//库所初始值（对于不同颜色的托肯有不同的初始个数）
    //每种颜色下可能发生冲突的变迁个数
    int num_of_transition_conflict[Max_color_num_ofplace];
    //所有与此库所连接的可能产生冲突的后置变迁的编号 对于不同颜色的托肯有不同的可能发生冲突的变迁组
    int id_of_transition_conflict[Max_color_num_ofplace][Max_inout_num];
    //所有与此库所连接的可能产生冲突的后置变迁中可能发生冲突的变迁规则编号 对于不同颜色的托肯有不同的可能发生冲突的变迁的变迁规则组
    int id_of_transition_rule_conflict[Max_color_num_ofplace][Max_inout_num];
    int number_of_prearcs;//库所前置弧的个数
    int number_of_postarcs;//库所后置弧的个数
    int id_of_prearcs[Max_inout_num];//库所前置弧的编号数组
    int id_of_color_prearcs[Max_inout_num]; //库所前置弧所对应颜色在库所颜色中的编号
    int inc_from_prearcs[Max_inout_num];//库所前置弧对库所的影响数组
    int id_of_postarcs[Max_inout_num];//库所后置弧的编号数组
    int id_of_color_postarcs[Max_inout_num]; //库所后置弧所对应颜色在库所颜色中的编号
    int dec_from_postarcs[Max_inout_num];//库所后置弧对库所的影响数组
    //struct place *next;
};

struct transition{
    int id;//变迁的编号
    int number_of_rules;//变迁发生规则的个数
    int number_of_prearcs[Max_rule_num];//每个变迁规则下前置弧的个数
    int number_of_postarcs[Max_rule_num];//每个变迁规则下后置弧的个数
    int id_of_prearcs[Max_rule_num][Max_color_num_inrule];//每个变迁规则对应的前置弧的编号
    int id_of_postarcs[Max_rule_num][Max_color_num_inrule];//每个变迁规则对应的后置弧的编号
    int dec_to_prearcs[Max_rule_num][Max_color_num_inrule];//每个变迁规则下对相应前置弧的影响数组
    int inc_to_postarcs[Max_rule_num][Max_color_num_inrule];//每个变迁规则下对相应后置弧的影响数组
    int maxsize_of_prearcs[Max_rule_num][Max_color_num_inrule];//每个变迁规则下前置弧所连库所的该色托肯最大容量
    int maxsize_of_postarcs[Max_rule_num][Max_color_num_inrule];//每个变迁规则下后置弧所连库所的该色托肯最大容量
    //struct transition *next;
};
#endif // PETRI_H
