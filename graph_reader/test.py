import subprocess as sbp
res = sbp.check_output("make clean", shell = True)
res = sbp.check_output("make", shell = True)
data = "toy.dat_" 
b = ".bin"
p = "toy_graph/"
cmd = f"./graph_loader.bin {p}{data}beg_pos{b} {p}{data}csr{b} {p}{data}weight{b}"
print(cmd)
res = sbp.check_output(cmd, shell=True)
print(str(res, encoding = 'utf8'))
