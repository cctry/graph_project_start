import subprocess as sbp
res = sbp.check_output("make", shell = True)
#data = "toy.dat_"
#p = "toy_graph/"
data = "out.orkut-links_"
p = "/mnt/e/graphs/orkut-links/"

beg_pos = "beg_pos.bin" 
csr = "csr.bin"
weight = "weight.bin"

cmd = f"./graph_loader.bin {p}{data}{beg_pos} {p}{data}{csr} {p}{data}{weight}"
print(cmd)
res = sbp.check_output(cmd, shell=True)
print(str(res, encoding = 'utf8'))
