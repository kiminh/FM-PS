service ParameterServer{
  //worker可以pull第t轮的部分参数到本地(
  //取决于server分到的参数，server之间交集为空，并集为全部参数)
  binary pull(1:i32 epoch),
  void push(1:i32 epoch, 2:binary gradient)
}