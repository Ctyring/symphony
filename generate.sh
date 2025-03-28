#/bin/sh

command_error_exit() {
    #! 执行命令，如果命令执行失败，则退出脚本
    $*
    if [ $? -ne 0 ]
    then
        exit 1
    fi
}

if [ $# -lt 2 ]
then
    echo "use [$0 project_name namespace]"
    exit 0
fi

project_name=$1
namespace=$2

command_error_exit mkdir $project_name
command_error_exit cd $project_name
command_error_exit git clone https://github.com/Ctyring/symphony.git
command_error_exit cp symphony/Makefile .
command_error_exit cp -rf symphony/template/* .
command_error_exit cp -rf symphony/template/* .
# 替换模板中的项目名、命名空间
command_error_exit mv template ${namespace}
command_error_exit sed -i "s/project_name/${project_name}/g" CMakeLists.txt
command_error_exit sed -i "s/template/${namespace}/g" CMakeLists.txt
command_error_exit sed -i "s/project_name/${project_name}/g" move.sh
command_error_exit cd ${namespace}
command_error_exit sed -i "s/name_space/${namespace}/g" `ls .`
command_error_exit sed -i "s/project_name/${project_name}/g" `ls .`

echo "create module ${project_name} -- ${namespace} ok"