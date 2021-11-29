#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct NODE
{                      
    struct NODE *next; 
    int ham_count;     
    int spam_count;
    char *word;
};

int find_NODE(const char *target, struct NODE *node_ptr, int spam_flag);
int insert_NODE(char *target, struct NODE *node_ptr, int spam_flag);
void stream_list(struct NODE *node);
void destroy_list(struct NODE *head);
int file_read(const char *path, struct NODE *node_ptr);
int get_node_spam_count(struct NODE *node_ptr, const char* target);
int get_node_ham_count(struct NODE *node_ptr, const char* target);
int calc_prob(const char *path, struct NODE *node_ptr, float THRESHHOLD);

int main(int argc, char *argv[])
{
    struct NODE *head = malloc(sizeof(struct NODE));
    head->next = NULL;
    head->word = "list of head";
    head->ham_count = -1;
    head->spam_count = -1;
    float prob_spam = 0.f;
    float THRESHHOLD = 0.5f;
    file_read("/home/ahn_ssu/zDM/datasets/train/dataset_ham_train100.csv", head);
    file_read("/home/ahn_ssu/zDM/datasets/train/dataset_spam_train100.csv", head);


    calc_prob("/home/ahn_ssu/zDM/datasets/test/dataset_ham_test20.csv", head, THRESHHOLD);
    calc_prob("/home/ahn_ssu/zDM/datasets/test/dataset_spam_test20.csv", head, THRESHHOLD);

    destroy_list(head);

    return 0;
}

int file_read(const char *path, struct NODE *node_ptr)
{
    char *p;
    char str_tmp[BUFSIZ];
    FILE *pFile = NULL;
    pFile = fopen(path, "r");
    if (pFile != NULL)
    {
        fgets(str_tmp, BUFSIZ, pFile); // 레이블 제거
        while (!feof(pFile))
        {
            fgets(str_tmp, BUFSIZ, pFile);
            if (feof(pFile))
                break;
            char content[BUFSIZ] = "";

            p = strtok(str_tmp, ",");

            p = strtok(NULL, ",");
            int spam_flag = 0;
            if (strcmp(p, "ham"))
                spam_flag = 1; // stccmp 같으면 0 리턴

            p = strtok(NULL, ",");
            char *p_dc, *p_dc2, *enter;
            p_dc = strchr(p, '"');
            strcat(content, p_dc + 1); // "의 시작부터
            if (p_dc == NULL)
                printf("p_dc is null\n");
            fgets(str_tmp, BUFSIZ, pFile);
            p_dc = strchr(p_dc + 1, '"');
            p_dc2 = strstr(str_tmp, "\"\"");
            if (p_dc2 != NULL)
                p_dc = NULL;

            while (!p_dc) // 다음 "를 만날 때 까지
            {
                strcat(content, str_tmp);
                fgets(str_tmp, BUFSIZ, pFile);
                p_dc = strchr(str_tmp, '"');
                p_dc2 = strstr(str_tmp, "\"\"");
                if (p_dc2 != NULL)
                    p_dc = NULL;
            }
            strcat(content, str_tmp);

            char *token = strtok(content, " ");
            while (token != NULL)
            {

                if(strlen(token) > 1){
                if(find_NODE(token, node_ptr->next, spam_flag) == 0)
                    insert_NODE(token, node_ptr, spam_flag);
                }

                token = strtok(NULL, " ");
                if (token == NULL)
                    break;
            }

            
        }

        
    }
    else
    {
        fclose(pFile);
        return 0;
    }
    printf("왜 리턴할 때 segmentation fault가 뜨나요\n");
    return 1;
}

int find_NODE(const char *target, struct NODE *node_ptr, int spam_flag)
{
    if (node_ptr == NULL)
        return 0;

    int fine = 0;
    while (node_ptr != NULL)
    {
        if (strcmp(node_ptr->word, target) == 0)
        { // 해당 단어가 이미 기록 된 경우
            if (spam_flag == 0)
                node_ptr->ham_count++;
            else
                node_ptr->spam_count++;

            fine = 1;
            break;
        }
        node_ptr = node_ptr->next;
    }

    if (fine)
        return 1;
    else {return 0;}
};

int insert_NODE(char *target, struct NODE *node_ptr, int spam_flag)
{
    if (node_ptr == NULL)
    {
        printf("input node err\n");
        return -1;
    }

    while (node_ptr->next != NULL)
    {
        node_ptr = node_ptr->next;
    }
    struct NODE *new = malloc(sizeof(struct NODE));
    new->word = target;
    new->next = NULL;
    new->ham_count = 0;
    new->spam_count = 0;

    if (spam_flag)
        new->spam_count++;
    else
        new->ham_count++;

    node_ptr->next = new;
    return 1;
};

void stream_list(struct NODE *node)
{
    if (node == NULL)
    {
        printf("done\n");
        return;
    }
    else
    {
        printf("node info, word:%s, spam:%d, ham:%d\n", node->word, node->spam_count, node->ham_count);
        return stream_list(node->next);
    }
}

void destroy_list(struct NODE *head)
{

    if (head->next == NULL)
    {
        free(head);
    }
    else
    {
        destroy_list(head->next);
        free(head);
    }
}

int get_node_ham_count(struct NODE *node_ptr, const char* target){
    while (node_ptr->next != NULL)
    {
        if (strcmp(node_ptr->word, target) == 0) return node_ptr->ham_count;

        node_ptr = node_ptr->next;
    }

    return -1;
}

int get_node_spam_count(struct NODE *node_ptr, const char* target){
    while (node_ptr->next != NULL)
    {
        if (strcmp(node_ptr->word, target) == 0) return node_ptr->ham_count;

        node_ptr = node_ptr->next;
    }

    return -1;
}


int calc_prob(const char *path, struct NODE *node_ptr, float THRESHHOLD)
{
    char *p;
    char str_tmp[BUFSIZ];
    FILE *pFile = NULL;
    int ham_cnt=0, spam_cnt=0, iter=0;

    pFile = fopen(path, "r");
    if (pFile != NULL)
    {
        fgets(str_tmp, BUFSIZ, pFile); // 레이블 제거
        while (!feof(pFile))
        {
            
            fgets(str_tmp, BUFSIZ, pFile);
            if (feof(pFile))
                break;
            iter++;
            char content[BUFSIZ] = "";

            p = strtok(str_tmp, ",");

            p = strtok(NULL, ",");
            int spam_flag = 0;
            if (strcmp(p, "ham"))
                spam_flag = 1; // stccmp 같으면 0 리턴

            p = strtok(NULL, ",");
            char *p_dc, *p_dc2, *enter;
            p_dc = strchr(p, '"');
            strcat(content, p_dc + 1); // "의 시작부터
            if (p_dc == NULL)
                printf("p_dc is null\n");
            fgets(str_tmp, BUFSIZ, pFile);
            p_dc = strchr(p_dc + 1, '"');
            p_dc2 = strstr(str_tmp, "\"\"");
            if (p_dc2 != NULL)
                p_dc = NULL;

            while (!p_dc) // 다음 "를 만날 때 까지
            {
                strcat(content, str_tmp);
                fgets(str_tmp, BUFSIZ, pFile);
                p_dc = strchr(str_tmp, '"');
                p_dc2 = strstr(str_tmp, "\"\"");
                if (p_dc2 != NULL)
                    p_dc = NULL;
            }
            strcat(content, str_tmp);

            float prob_T=1.f, prob_nT=1.f, result = 0.f; // for A / (A+B)
            char *token = strtok(content, " ");
            while (token != NULL)
            {

                if(strlen(token) > 1){
                if(find_NODE(token, node_ptr->next, spam_flag) != 0)
                    spam_cnt = get_node_spam_count(node_ptr, token);
                    ham_cnt = get_node_ham_count(node_ptr, token);

                    prob_T *= spam_cnt / (spam_cnt+ham_cnt);
                    prob_nT += ham_cnt / (spam_cnt+ham_cnt);
                }

                token = strtok(NULL, " ");
                if (token == NULL)
                    break;
            }
            result = prob_T/(prob_nT+prob_T);

            printf("#%d sample prob=%f, threshold=%f, classification result: %s\n",iter,result,THRESHHOLD,result>THRESHHOLD?"SPAM":"NON-SPAM");
        }
    }
    else
    {
        fclose(pFile);
        return 0;
    }
    return 1;
}