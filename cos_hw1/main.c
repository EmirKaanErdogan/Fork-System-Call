#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>	//  printf
#include <unistd.h>	//  fork
#include <stdlib.h>	//  exit
#include <sys/wait.h>	//   wait


void create_tree(int height){
    if(height==0){
        printf("The last Parent Node with the pid: %d ,and it is created from the parent with pid: %d \n",getpid(),getppid());
        int last_node_pid= fork(); 
        if(last_node_pid>0){
            wait(NULL) ;
        }
        if(last_node_pid==0){
            printf("Left Child Node with pid:%d, and it is created from the parent: %d",getpid(),getppid());
        }
        return  ; 
    } 
    int pid= fork(); 
    if(pid>0){
        // parent ; 
        int pid2=fork(); 
        if(pid2>0){
            // parent
            printf("Parent Node with pid: %d\n",getpid()); 
            waitpid(pid2, NULL, 0);
        }
        if(pid2==0){
            // right child ; 
            printf("Rigth Child with pid: %d ,created from the parent with pid: %d \n",getpid(),getppid()) ;
            create_tree(--height); 
        }
    }
    else if(pid==0){
        // left child
        printf("Left Child with pid: %d, created from the parent with pid: %d \n",getpid(),getppid()); 
        waitpid(pid, NULL, 0);
    }
}
void create_tree_q2(int height,int m){
    if(height==0){
        int last_node_pid= fork(); 
        if(last_node_pid>0){
            printf("Last Parent of the right subtree: %d ,and is created from the parent: %d \n",getpid(),getppid());
        }
        else if(last_node_pid==0){
            // child 
            printf("Left Child with pid:%d, created from the parent with pid: %d \n",getpid(),getppid());
            for(int i=0;i<m-1;i++){
                int left_child= fork() ;
                if(left_child>0){
                    printf("The parent Node with the pid: %d, and it is created from the parent with pid: %d \n",getpid(),getppid());
                    waitpid(left_child,NULL,0) ;
                }
                else if(left_child==0){
                    printf("Left Child with pid: %d, created from the parent with pid: %d \n",getpid(),getppid());
                    waitpid(left_child, NULL, 0);   
                }
            }
            wait(NULL) ;
        }

        return  ; 
    }
    int pid3=fork() ; 
    if(pid3>0){
        int pid4=fork();
        if(pid4>0){
            // parent
            printf("Parent Node with pid: %d\n",getpid()); 
            waitpid(pid4, NULL, 0);
        }
        else if(pid4==0){
            // right child ; 
            printf("Rigth Child with pid: %d ,created from the parent with pid: %d \n",getpid(),getppid()) ;
            create_tree_q2(--height,m); 
        }
    }
    else if(pid3==0){
        // left child ; 
        printf("Left Child with pid:%d, created from the parent with pid: %d \n",getpid(),getppid());
        for(int i=0;i<m-1;i++){
            int temp= fork(); 
            if(temp>0){
                printf("Left Child with pid:%d, created from the parent with pid: %d \n",getpid(),getppid());
                waitpid(temp,NULL,0); 
            }
            else if(temp==0){
                printf("Left Child with pid:%d, created from the parent: %d \n",getpid(),getppid());
            }
        }
    }

}
int main(){
    int N; 
    printf("Please enter the N value: "); 
    scanf("%d",&N); 
    //printf("The root Node's pid: %d\n",getpid());
    //create_tree(N); 
    int M ;
    printf("Please enter the M value: "); 
    scanf("%d",&M) ;
    printf("The root Node's pid: %d\n",getpid());
    create_tree_q2(N,M) ;

    return 0; 
}