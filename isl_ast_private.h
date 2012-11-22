#ifndef ISL_AST_PRIVATE_H
#define ISL_AST_PRIVATE_H

#include <isl/aff.h>
#include <isl/ast.h>
#include <isl/set.h>
#include <isl/map.h>
#include <isl/vec.h>
#include <isl/list.h>

/* An expression is either an integer, an identifier or an operation
 * with zero or more arguments.
 */
struct isl_ast_expr {
	int ref;

	isl_ctx *ctx;

	enum isl_ast_expr_type type;

	union {
		isl_int i;
		isl_id *id;
		struct {
			enum isl_ast_op_type op;
			unsigned n_arg;
			isl_ast_expr **args;
		} op;
	} u;
};

#undef EL
#define EL isl_ast_expr

#include <isl_list_templ.h>

__isl_give isl_ast_expr *isl_ast_expr_alloc_int(isl_ctx *ctx, isl_int i);
__isl_give isl_ast_expr *isl_ast_expr_alloc_int_si(isl_ctx *ctx, int i);
__isl_give isl_ast_expr *isl_ast_expr_alloc_op(isl_ctx *ctx,
	enum isl_ast_op_type op, int n_arg);
__isl_give isl_ast_expr *isl_ast_expr_alloc_binary(enum isl_ast_op_type type,
	__isl_take isl_ast_expr *expr1, __isl_take isl_ast_expr *expr2);

#undef EL
#define EL isl_ast_node

#include <isl_list_templ.h>

/* A node is either a block, an if, a for or a user node.
 * "else_node" is NULL if the if node does not have an else branch.
 * "cond" and "inc" are NULL for degenerate for nodes.
 */
struct isl_ast_node {
	int ref;

	isl_ctx *ctx;
	enum isl_ast_node_type type;

	union {
		struct {
			isl_ast_node_list *children;
		} b;
		struct {
			isl_ast_expr *guard;
			isl_ast_node *then;
			isl_ast_node *else_node;
		} i;
		struct {
			unsigned degenerate : 1;
			isl_ast_expr *iterator;
			isl_ast_expr *init;
			isl_ast_expr *cond;
			isl_ast_expr *inc;
			isl_ast_node *body;
		} f;
		struct {
			isl_ast_expr *expr;
		} e;
	} u;

	isl_id *annotation;
};

__isl_give isl_ast_node *isl_ast_node_alloc_for(__isl_take isl_id *id);
__isl_give isl_ast_node *isl_ast_node_for_mark_degenerate(
	__isl_take isl_ast_node *node);
__isl_give isl_ast_node *isl_ast_node_alloc_if(__isl_take isl_ast_expr *guard);
__isl_give isl_ast_node *isl_ast_node_alloc_block(
	__isl_take isl_ast_node_list *list);
__isl_give isl_ast_node *isl_ast_node_from_ast_node_list(
	__isl_take isl_ast_node_list *list);
__isl_give isl_ast_node *isl_ast_node_for_set_body(
	__isl_take isl_ast_node *node, __isl_take isl_ast_node *body);
__isl_give isl_ast_node *isl_ast_node_if_set_then(
	__isl_take isl_ast_node *node, __isl_take isl_ast_node *child);

struct isl_ast_print_options {
	int ref;
	isl_ctx *ctx;

	__isl_give isl_printer *(*print_for)(__isl_take isl_printer *p,
		__isl_take isl_ast_print_options *options,
		__isl_keep isl_ast_node *node, void *user);
	void *print_for_user;
	__isl_give isl_printer *(*print_user)(__isl_take isl_printer *p,
		__isl_take isl_ast_print_options *options,
		__isl_keep isl_ast_node *node, void *user);
	void *print_user_user;
};

__isl_give isl_printer *isl_ast_node_list_print(
	__isl_keep isl_ast_node_list *list, __isl_take isl_printer *p,
	__isl_keep isl_ast_print_options *options);

#endif
