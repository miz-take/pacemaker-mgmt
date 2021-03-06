/*
 * Copyright (c) 2004 Intel Corp.
 *
 * Author: Zou Yixiong (yixiong.zou@intel.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */

/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.iterate.conf,v 5.9 2003/06/04 00:14:41 hardaker Exp $
 */

#include <pygui_internal.h>

#ifdef PACKAGE_BUGREPORT
#undef PACKAGE_BUGREPORT
#endif
#ifdef PACKAGE_NAME
#undef PACKAGE_NAME
#endif
#ifdef PACKAGE_STRING
#undef PACKAGE_STRING
#endif
#ifdef PACKAGE_TARNAME
#undef PACKAGE_TARNAME
#endif
#ifdef PACKAGE_VERSION
#undef PACKAGE_VERSION
#endif

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "LHAMembershipTable.h"

#include "hbagent.h"

static GPtrArray * gMembershipInfo = NULL;
extern const int snmp_cache_time_out;

int LHAMembershipTable_load(netsnmp_cache *cache, void *vmagic);
void LHAMembershipTable_free(netsnmp_cache *cache, void *vmagic);

/** Initialize the LHAMembershipTable table by defining its contents and how it's structured */
void
initialize_table_LHAMembershipTable(void)
{
    static oid LHAMembershipTable_oid[] = {1,3,6,1,4,1,4682,6};
    netsnmp_table_registration_info *table_info;
    netsnmp_handler_registration *my_handler;
    netsnmp_iterator_info *iinfo;

    /** create the table registration information structures */
    table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);
    iinfo = SNMP_MALLOC_TYPEDEF(netsnmp_iterator_info);

    /** if your table is read only, it's easiest to change the
        HANDLER_CAN_RWRITE definition below to HANDLER_CAN_RONLY */
    my_handler = netsnmp_create_handler_registration("LHAMembershipTable",
                                             LHAMembershipTable_handler,
                                             LHAMembershipTable_oid,
                                             OID_LENGTH(LHAMembershipTable_oid),
                                             HANDLER_CAN_RONLY);
            
    if (!my_handler || !table_info || !iinfo) {
        snmp_log(LOG_ERR, "malloc failed in initialize_table_LHAMembershipTable");
	SNMP_FREE(iinfo);
	SNMP_FREE(table_info);
        return; /* Serious error. */
    }

    /***************************************************
     * Setting up the table's definition
     */
    netsnmp_table_helper_add_indexes(table_info,
                                  ASN_INTEGER, /* index: LHAMemberIndex */
                             0);

    /** Define the minimum and maximum accessible columns.  This
        optimizes retrival. */
    table_info->min_column = 2;
    table_info->max_column = 7;

    /* iterator access routines */
    iinfo->get_first_data_point = LHAMembershipTable_get_first_data_point;
    iinfo->get_next_data_point = LHAMembershipTable_get_next_data_point;

    /** tie the two structures together */
    iinfo->table_reginfo = table_info;

    /***************************************************
     * registering the table with the master agent
     */
    DEBUGMSGTL(("initialize_table_LHAMembershipTable",
                "Registering table LHAMembershipTable as a table iterator\n"));		 
    netsnmp_register_table_iterator(my_handler, iinfo);

    /*
     * .... with a local cache
     */
    netsnmp_inject_handler(my_handler,
	 netsnmp_get_cache_handler(snmp_cache_time_out, 
				   LHAMembershipTable_load,
				   LHAMembershipTable_free,
				   LHAMembershipTable_oid,
				   OID_LENGTH(LHAMembershipTable_oid)));
}

/** Initializes the LHAMembershipTable module */
void
init_LHAMembershipTable(void)
{

  /** here we initialize all the tables we're planning on supporting */
    initialize_table_LHAMembershipTable();
}

/** returns the first data point within the LHAMembershipTable table data.

    Set the my_loop_context variable to the first data point structure
    of your choice (from which you can find the next one).  This could
    be anything from the first node in a linked list, to an integer
    pointer containing the beginning of an array variable.

    Set the my_data_context variable to something to be returned to
    you later (in your main LHAMembershipTable_handler routine) that will provide
    you with the data to return in a given row.  This could be the
    same pointer as what my_loop_context is set to, or something
    different.

    The put_index_data variable contains a list of snmp variable
    bindings, one for each index in your table.  Set the values of
    each appropriately according to the data matching the first row
    and return the put_index_data variable at the end of the function.
*/
netsnmp_variable_list *
LHAMembershipTable_get_first_data_point(void **my_loop_context, void **my_data_context,
                          netsnmp_variable_list *put_index_data,
                          netsnmp_iterator_info *mydata)
{
    if (gMembershipInfo && gMembershipInfo->len == 0) 
	return NULL;

    *my_loop_context = NULL;
    return LHAMembershipTable_get_next_data_point( my_loop_context,
	    			my_data_context,
	    			put_index_data,
	    			mydata);
}

/** functionally the same as LHAMembershipTable_get_first_data_point, but
   my_loop_context has already been set to a previous value and should
   be updated to the next in the list.  For example, if it was a
   linked list, you might want to cast it to your local data type and
   then return my_loop_context->next.  The my_data_context pointer
   should be set to something you need later (in your main
   LHAMembershipTable_handler routine) and the indexes in put_index_data updated
   again. */
netsnmp_variable_list *
LHAMembershipTable_get_next_data_point(void **my_loop_context, void **my_data_context,
                         netsnmp_variable_list *put_index_data,
                         netsnmp_iterator_info *mydata)
{
    static size_t i = 0;
    netsnmp_variable_list *vptr;
#if SUPPORT_HEARTBEAT
    SaClmClusterNotificationT * info;
#endif

    if (*my_loop_context != NULL) {
	i = *((size_t *) *my_loop_context);
    } else {
	i = 0;
    }

    if (!gMembershipInfo || i >= gMembershipInfo->len) 
	return NULL;

    vptr = put_index_data;
#if SUPPORT_HEARTBEAT
    info = (SaClmClusterNotificationT *) g_ptr_array_index(gMembershipInfo, i);
#endif

    snmp_set_var_value(vptr, (u_char *) &i, sizeof(i));
    vptr = vptr->next_variable;

    i++;
    *my_loop_context = (void *) &i;
#if SUPPORT_HEARTBEAT
    *my_data_context = (void *) info;
#endif

    return put_index_data;
}

/** handles requests for the LHAMembershipTable table, if anything else needs to be done */
int
LHAMembershipTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info *request;
    netsnmp_table_request_info *table_info;
    netsnmp_variable_list *var;

#if SUPPORT_HEARTBEAT
    SaClmClusterNotificationT * entry;
#endif
    int member;
    
    for(request = requests; request; request = request->next) {
        var = request->requestvb;
        if (request->processed != 0)
            continue;

        /** perform anything here that you need to do before each
           request is processed. */

        /** the following extracts the my_data_context pointer set in
           the loop functions above.  You can then use the results to
           help return data for the columns of the LHAMembershipTable table in question */
#if SUPPORT_HEARTBEAT
        entry = (SaClmClusterNotificationT *) 
	    netsnmp_extract_iterator_context(request);

        if (entry == NULL) {
            if (reqinfo->mode == MODE_GET) {
                netsnmp_set_request_error(reqinfo, request, SNMP_NOSUCHINSTANCE);
                continue;
            }
            /** XXX: no row existed, if you support creation and this is a
               set, start dealing with it here, else continue */
        }
#endif

        /** extracts the information about the table from the request */
        table_info = netsnmp_extract_table_info(request);
        /** table_info->colnum contains the column number requested */
        /** table_info->indexes contains a linked list of snmp variable
           bindings for the indexes of the table.  Values in the list
           have been set corresponding to the indexes of the
           request */
        if (table_info==NULL) {
            continue;
        }

        switch(reqinfo->mode) {
            /** the table_iterator helper should change all GETNEXTs
               into GETs for you automatically, so you don't have to
               worry about the GETNEXT case.  Only GETs and SETs need
               to be dealt with here */
            case MODE_GET:
                switch(table_info->colnum) {
                    case COLUMN_LHAMEMBERNAME:
#if SUPPORT_HEARTBEAT
                        snmp_set_var_typed_value(var, 
				ASN_OCTET_STR, 
				(u_char *) entry->clusterNode.nodeName.value, 
				strlen((char *)entry->clusterNode.nodeName.value) + 1);
#endif
                        break;

                    case COLUMN_LHAMEMBERADDRESS:
#if SUPPORT_HEARTBEAT
                        snmp_set_var_typed_value(var, 
				ASN_OCTET_STR, 
				(u_char *) entry->clusterNode.nodeAddress.value, 
				SA_CLM_MAX_ADDRESS_LENGTH);
#endif
                        break;

                    case COLUMN_LHAMEMBERCLUSTERNAME:
#if SUPPORT_HEARTBEAT
                        snmp_set_var_typed_value(var, 
				ASN_OCTET_STR, 
				(u_char *) entry->clusterNode.clusterName.value, 
				strlen((char *)entry->clusterNode.clusterName.value) + 1);
#endif
                        break;

                    case COLUMN_LHAMEMBERISMEMBER:
#if SUPPORT_HEARTBEAT
			if (entry->clusterNode.member)
			    member = 1;
			else 
			    member = 2;
#endif

                        snmp_set_var_typed_value(var, 
				ASN_INTEGER, 
				(u_char *) &member, 
				sizeof(member));
                        break;

                    case COLUMN_LHAMEMBERLASTCHANGE:
#if SUPPORT_HEARTBEAT
                        snmp_set_var_typed_value(var, 
				ASN_INTEGER, 
				(u_char *) & entry->clusterChanges, 
				sizeof(entry->clusterChanges));
#endif
                        break;

                    case COLUMN_LHAMEMBERBOOTTIME:
#if SUPPORT_HEARTBEAT
                        snmp_set_var_typed_value(var, 
				ASN_TIMETICKS, 
				(u_char *) & entry->clusterNode.bootTimestamp, 
				sizeof(entry->clusterNode.bootTimestamp));
#endif
                        break;

                    default:
                        /** We shouldn't get here */
                        snmp_log(LOG_ERR, "problem encountered in LHAMembershipTable_handler: unknown column\n");
                }
                break;

            case MODE_SET_RESERVE1:
                /** set handling... */

            default:
                snmp_log(LOG_ERR, "problem encountered in LHAMembershipTable_handler: unsupported mode\n");
        }
    }
    return SNMP_ERR_NOERROR;
}

int 
LHAMembershipTable_load(netsnmp_cache *cache, void *vmagic)
{
    LHAMembershipTable_free(cache, vmagic);

    gMembershipInfo = get_hb_info(LHA_MEMBERSHIPINFO);

    return 0;
}

void 
LHAMembershipTable_free(netsnmp_cache *cache, void *vmagic)
{
    return;
}



