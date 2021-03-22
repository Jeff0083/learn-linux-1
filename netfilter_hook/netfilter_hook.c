#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/initrd.h>
#include <linux/types.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/tcp.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>


MODULE_LICENSE("GPLv3");
MODULE_AUTHOR("Jianping");
MODULE_DESCRIPTION("Netfliter Hook");

static unsigned int nf_ipv4_test_hook(void *priv,
					 struct sk_buff *skb,
					 const struct nf_hook_state *state);

static const struct nf_hook_ops ipv4_test_in_ops = {
	.hook	= nf_ipv4_test_hook,
	.pf	= NFPROTO_IPV4,
	.hooknum = NF_INET_LOCAL_IN, 
	.priority = NF_IP_PRI_FIRST,
};



void hdr_dump(struct ethhdr *ehdr) {
    printk("[MAC_DES:%x,%x,%x,%x,%x,%x " 
           " MAC_SRC: %x,%x,%x,%x,%x,%x Prot:%x]\n",
           ehdr->h_dest[0],ehdr->h_dest[1],ehdr->h_dest[2],ehdr->h_dest[3],
           ehdr->h_dest[4],ehdr->h_dest[5],ehdr->h_source[0],ehdr->h_source[1],
           ehdr->h_source[2],ehdr->h_source[3],ehdr->h_source[4],
           ehdr->h_source[5],ehdr->h_proto);
}

#define NIPQUAD(addr) \
        ((unsigned char *)&addr)[0], \
        ((unsigned char *)&addr)[1], \
        ((unsigned char *)&addr)[2], \
        ((unsigned char *)&addr)[3]
#define NIPQUAD_FMT "%u.%u.%u.%u"



static unsigned int nf_ipv4_test_hook(void *priv,
                                   struct sk_buff *skb,
                                   const struct nf_hook_state *state)
{
  struct ethhdr *eth_header;
  struct iphdr *ip_header;
  
  eth_header = (struct ethhdr *)(skb_mac_header(skb));
  ip_header = (struct iphdr *)(skb_network_header(skb));

  if(NULL != eth_header->h_dest[0]){
     
  	hdr_dump(eth_header);
  }

  if(NULL != ip_header->saddr){

	printk("src IP:'"NIPQUAD_FMT"', dst IP:'"NIPQUAD_FMT"' \n",
	NIPQUAD(ip_header->saddr), NIPQUAD(ip_header->daddr));
  }
  return NF_ACCEPT;	
}




static int __init init_nf_test(void) {
  int ret;
  ret =nf_register_net_hook(&init_net, &ipv4_test_in_ops);
  if (ret < 0) {
    printk("register nf hook fail\n");
    return ret;
  }
  printk(KERN_NOTICE "register nf test hook\n");
  return 0;
}

static void __exit exit_nf_test(void) {
  
  nf_unregister_net_hook(&init_net, &ipv4_test_in_ops);
  printk(KERN_NOTICE "unregister nf test hook\n");

}

module_init(init_nf_test);
module_exit(exit_nf_test);






