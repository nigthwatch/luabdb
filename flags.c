/*
* Copyright (c) 2010 Rob Hoelz <rob@hoelz.ro>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#include <db.h>
#include <lua.h>

struct flag_spec {
    const char *name;
    int value;
};
#define _(s) { #s, s }

struct flag_spec flags[] = {
    _(DB_CREATE),
    _(DB_DURABLE_UNKNOWN),
    _(DB_FORCE),
    _(DB_MULTIVERSION),
    _(DB_NOMMAP),
    _(DB_RDONLY),
    _(DB_RECOVER),
    _(DB_THREAD),
    _(DB_TRUNCATE),
    _(DB_TXN_NOSYNC),
    _(DB_TXN_NOWAIT),
    _(DB_TXN_NOT_DURABLE),
    _(DB_TXN_WRITE_NOSYNC),
    _(DB_IGNORE_LEASE),
    _(DB_AUTO_COMMIT),
    _(DB_READ_COMMITTED),
    _(DB_DEGREE_2),
    _(DB_READ_UNCOMMITTED),
    _(DB_DIRTY_READ),
    _(DB_TXN_SNAPSHOT),
    _(DB_INIT_CDB),
    _(DB_INIT_LOCK),
    _(DB_INIT_LOG),
    _(DB_INIT_MPOOL),
    _(DB_INIT_REP),
    _(DB_INIT_TXN),
    _(DB_LOCKDOWN),
    _(DB_PRIVATE),
    _(DB_RECOVER_FATAL),
    _(DB_REGISTER),
    _(DB_SYSTEM_MEM),
    _(DB_EXCL),
    _(DB_FCNTL_LOCKING),
    _(DB_NO_AUTO_COMMIT),
    _(DB_RDWRMASTER),
    _(DB_WRITEOPEN),
    _(DB_IMMUTABLE_KEY),
    _(DB_TXN_SYNC),
    _(DB_TXN_WAIT),
    _(DB_CKP_INTERNAL),
    _(DB_ENCRYPT_AES),
    _(DB_CDB_ALLDB),
    _(DB_DIRECT_DB),
    _(DB_DSYNC_DB),
    _(DB_NOLOCKING),
    _(DB_NOPANIC),
    _(DB_OVERWRITE),
    _(DB_PANIC_ENVIRONMENT),
    _(DB_REGION_INIT),
    _(DB_TIME_NOTGRANTED),
    _(DB_YIELDCPU),
    _(DB_UPGRADE),
    _(DB_VERIFY),
    _(DB_FREELIST_ONLY),
    _(DB_FREE_SPACE),
    _(DB_DIRECT),
    _(DB_EXTENT),
    _(DB_ODDFILESIZE),
    _(DB_CHKSUM),
    _(DB_DUP),
    _(DB_DUPSORT),
    _(DB_ENCRYPT),
    _(DB_INORDER),
    _(DB_RECNUM),
    _(DB_RENUMBER),
    _(DB_REVSPLITOFF),
    _(DB_SNAPSHOT),
    _(DB_FAST_STAT),
    _(DB_STAT_ALL),
    _(DB_STAT_CLEAR),
    _(DB_STAT_LOCK_CONF),
    _(DB_STAT_LOCK_LOCKERS),
    _(DB_STAT_LOCK_OBJECTS),
    _(DB_STAT_LOCK_PARAMS),
    _(DB_STAT_MEMP_HASH),
    _(DB_STAT_SUBSYSTEM),
    _(DB_JOIN_NOSORT),
    _(DB_AGGRESSIVE),
    _(DB_NOORDERCHK),
    _(DB_ORDERCHKONLY),
    _(DB_PR_PAGE),
    _(DB_PR_RECOVERYTEST),
    _(DB_PRINTABLE),
    _(DB_SALVAGE),
    _(DB_UNREF),
    _(DB_REP_ANYWHERE),
    _(DB_REP_NOBUFFER),
    _(DB_REP_PERMANENT),
    _(DB_REP_REREQUEST),
    _(DB_MUTEX_ALLOCATED),
    _(DB_MUTEX_LOCKED),
    _(DB_MUTEX_LOGICAL_LOCK),
    _(DB_MUTEX_PROCESS_ONLY),
    _(DB_MUTEX_SELF_BLOCK),
    _(DB_LOCK_NORUN),
    _(DB_LOCK_DEFAULT),
    _(DB_LOCK_EXPIRE),
    _(DB_LOCK_MAXLOCKS),
    _(DB_LOCK_MAXWRITE),
    _(DB_LOCK_MINLOCKS),
    _(DB_LOCK_MINWRITE),
    _(DB_LOCK_OLDEST),
    _(DB_LOCK_RANDOM),
    _(DB_LOCK_YOUNGEST),
    _(DB_LOCK_NOWAIT),
    _(DB_LOCK_RECORD),
    _(DB_LOCK_SET_TIMEOUT),
    _(DB_LOCK_SWITCH),
    _(DB_LOCK_UPGRADE),
    _(DB_SET_LOCK_TIMEOUT),
    _(DB_SET_TXN_NOW),
    _(DB_SET_TXN_TIMEOUT),
    _(DB_ARCH_ABS),
    _(DB_ARCH_DATA),
    _(DB_ARCH_LOG),
    _(DB_ARCH_REMOVE),
    _(DB_FLUSH),
    _(DB_LOG_CHKPNT),
    _(DB_LOG_COMMIT),
    _(DB_LOG_NOCOPY),
    _(DB_LOG_NOT_DURABLE),
    _(DB_LOG_WRNOSYNC),
    _(DB_MPOOL_CREATE),
    _(DB_MPOOL_DIRTY),
    _(DB_MPOOL_EDIT),
    _(DB_MPOOL_FREE),
    _(DB_MPOOL_LAST),
    _(DB_MPOOL_NEW),
    _(DB_MPOOL_DISCARD),
    _(DB_MPOOL_NOFILE),
    _(DB_MPOOL_UNLINK),
    _(MP_FILEID_SET),
    _(MP_FLUSH),
    _(MP_MULTIVERSION),
    _(MP_OPEN_CALLED),
    _(MP_READONLY),
    _(TXN_CHILDCOMMIT),
    _(TXN_COMPENSATE),
    _(TXN_DEADLOCK),
    _(TXN_LOCKTIMEOUT),
    _(TXN_MALLOC),
    _(TXN_NOSYNC),
    _(TXN_NOWAIT),
    _(TXN_PRIVATE),
    _(TXN_READ_COMMITTED),
    _(TXN_READ_UNCOMMITTED),
    _(TXN_RESTORED),
    _(TXN_SNAPSHOT),
    _(TXN_SYNC),
    _(TXN_WRITE_NOSYNC),
    _(TXN_SYNC_FLAGS),
    _(DB_REP_CONF_BULK),
    _(DB_REP_CONF_DELAYCLIENT),
    _(DB_REP_CONF_NOWAIT),
    _(DB_REP_CLIENT),
    _(DB_REP_ELECTION),
    _(DB_REP_MASTER),
    _(DB_REPMGR_ACKS_ALL),
    _(DB_REPMGR_ACKS_ALL_PEERS),
    _(DB_REPMGR_ACKS_NONE),
    _(DB_REPMGR_ACKS_ONE),
    _(DB_REPMGR_ACKS_ONE_PEER),
    _(DB_REPMGR_ACKS_QUORUM),
    _(DB_REP_ACK_TIMEOUT),
    _(DB_REP_CHECKPOINT_DELAY),
    _(DB_REP_CONNECTION_RETRY),
    _(DB_REP_ELECTION_RETRY),
    _(DB_REP_ELECTION_TIMEOUT),
    _(DB_REP_FULL_ELECTION_TIMEOUT),
    _(DB_REP_LEASE_TIMEOUT),
    _(DB_EVENT_NO_SUCH_EVENT),
    _(DB_EVENT_PANIC),
    _(DB_EVENT_REP_CLIENT),
    _(DB_EVENT_REP_ELECTED),
    _(DB_EVENT_REP_MASTER),
    _(DB_EVENT_REP_NEWMASTER),
    _(DB_EVENT_REP_PERM_FAILED),
    _(DB_EVENT_REP_STARTUPDONE),
    _(DB_EVENT_WRITE_FAILED),
    _(DB_SEQ_DEC),
    _(DB_SEQ_INC),
    _(DB_SEQ_RANGE_SET),
    _(DB_SEQ_WRAP),
    _(DB_SEQ_WRAPPED),
    _(DB_BTREE),
    _(DB_HASH),
    _(DB_RECNO),
    _(DB_QUEUE),
    _(DB_UNKNOWN),
    _(DB_RENAMEMAGIC),
    _(DB_BTREEVERSION),
    _(DB_BTREEOLDVER),
    _(DB_BTREEMAGIC),
    _(DB_HASHVERSION),
    _(DB_HASHOLDVER),
    _(DB_HASHMAGIC),
    _(DB_QAMVERSION),
    _(DB_QAMOLDVER),
    _(DB_QAMMAGIC),
    _(DB_SEQUENCE_VERSION),
    _(DB_SEQUENCE_OLDVER),
    _(DB_AFTER),
    _(DB_APPEND),
    _(DB_BEFORE),
    _(DB_CONSUME),
    _(DB_CONSUME_WAIT),
    _(DB_CURRENT),
    _(DB_FIRST),
    _(DB_GET_BOTH),
    _(DB_GET_BOTHC),
    _(DB_GET_BOTH_RANGE),
    _(DB_GET_RECNO),
    _(DB_JOIN_ITEM),
    _(DB_KEYFIRST),
    _(DB_KEYLAST),
    _(DB_LAST),
    _(DB_NEXT),
    _(DB_NEXT_DUP),
    _(DB_NEXT_NODUP),
    _(DB_NODUPDATA),
    _(DB_NOOVERWRITE),
    _(DB_NOSYNC),
    _(DB_POSITION),
    _(DB_PREV),
    _(DB_PREV_DUP),
    _(DB_PREV_NODUP),
    _(DB_SET),
    _(DB_SET_RANGE),
    _(DB_SET_RECNO),
    _(DB_UPDATE_SECONDARY),
    _(DB_WRITECURSOR),
    _(DB_WRITELOCK),
    _(DB_MULTIPLE),
    _(DB_MULTIPLE_KEY),
    _(DB_RMW),
    { NULL, 0 }
};
#undef _

int init_flags(lua_State *L)
{
    struct flag_spec *fs;

    lua_newtable(L);
    for(fs = flags; fs->name; fs++) {
        lua_pushinteger(L, fs->value);
        lua_setfield(L, -2, fs->name);
    }
    lua_setfield(L, 1, "flags");
    return 0;
}
