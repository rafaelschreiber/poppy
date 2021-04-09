module.exports={
    mode:'production',
    entry:'./main.js',
    output:{
        filename:'main.js',
        publicPath:'/dist/',
        libraryTarget:'var', 
        library:'ext',
    }
}